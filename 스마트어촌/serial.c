#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <mysql/mysql.h>
#include <wiringPi.h>
#include <wiringSerial.h>

static char * host = "localhost";
static char * user = "emb";
static char * pass = "kcci";
static char * dbname = "test";

char device[] = "/dev/ttyACM0";

int fd;
int str_len;
unsigned long baud = 9600;

int main ()
{
	MYSQL *conn;
	int res;
	char in_sql[300] ={0};

	char *pArray[5] = {0};
	char ser_buff[200] = {0};
	int buffindex = 0;
	char *pToken = NULL;
	int temp, moisture, water_level, wave_cnt, cds;

	int index, sql_index;
	int flag =0;

	conn = mysql_init(NULL);

	printf("%s \n", "Raspberry startup");
	fflush(stdout);

	if( (fd = serialOpen(device, baud) ) < 0 )
		exit(1);

	if(wiringPiSetup() == -1)
		return -1;

	if ( ! ( mysql_real_connect(conn, host, user, pass, dbname, 0 , NULL, 0) ) ) 
	{
		fprintf(stderr, "ERROR : %s[%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	else
		printf("Connection Successful!\n\n");

	while(1)
	{
		if(serialDataAvail(fd))
		{
			ser_buff[buffindex++] = serialGetchar(fd);
			//printf("ser_buff = %s \n", ser_buff);

			if( ser_buff[buffindex-1] == 'L')
			{
				flag = 1;
				ser_buff[buffindex-1] = '\0';
				str_len = strlen(ser_buff);
				//printf("test ser_buff = %s \n", ser_buff);
				pToken = strtok(ser_buff,":");
				int i = 0;
				while( pToken != NULL)
				{
//printf("check1");
					pArray[i] = pToken;
					i++;
					if( i > 6 )
						break;
					pToken = strtok(NULL,":");
					//printf("ser_buff[%d] = %s \n", i-1, pArray[i-1]);
				}


				temp = atoi(pArray[0]);
				moisture = atoi(pArray[1]);
				water_level = atoi(pArray[2]);
				wave_cnt = atoi(pArray[3]);
				cds = atoi(pArray[4]);

				printf("temp=%d, moisture=%d, water_level=%d, wave_cnt = %d, cds=%d", temp, moisture, water_level, wave_cnt, cds);
				for ( int i = 0 ; i <= str_len ; i++ )
				{
					ser_buff[i] = 0;
				}
				buffindex = 0;
			}
			if (temp < 100 && moisture < 100 )
			{
				if ( flag == 1)
				{
					sprintf(in_sql, "insert into sensing(id, date, time, Temperature, moisture, water_level, wave_cnt, cds) values (null, now(), now(),  %d, %d, %d, %d, %d)", temp, moisture, water_level, wave_cnt, cds);
					//sprintf(in_sql, "insert into sensing(id, date, time, Temperature, moisture, water_level) values (null, now(), now(),  %d, %d, %d)", temp, moisture, water_level);
					res = mysql_query(conn, in_sql);
					//printf("res = %d \n", res);
					if ( !res )
						printf("inserted %lu rows\n", (unsigned long)mysql_affected_rows(conn));
					else
						fprintf(stderr, "ERROR: %s[%d]\n", mysql_error(conn),mysql_errno(conn));
				}
				flag = 0;
			}
		}
	}
	mysql_close(conn);
	return EXIT_SUCCESS;
}
