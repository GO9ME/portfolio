<!DOCTYPE HTML>
<!--
	Epilogue by TEMPLATED
	templated.co @templatedco
	Released for free under the Creative Commons Attribution 3.0 license (templated.co/license)
-->
<html>
	<head>
		<title>IOT 어촌편</title>
		<meta charset="utf-8"/>
		<meta name="viewport" content="width=device-width, initial-scale=1" />
		<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css">
		<link rel="stylesheet" href="assets/css/main.css" />
		<style type = "text/css">
		.spec 
		{
			text-align:center;
			margin-bottom : 50px;
			margin-top : 50px;

		}
		.con
		{
			text-align:center;
		}
		table.type08 {
			border-collapse: collapse;
			text-align: center;
			line-height: 1.5;
			border-left: 1px solid #ccc;
			margin: 20px 10px;
		}

		table.type08 thead th {
			padding: 10px;
			font-weight: bold;
			border-top: 1px solid #ccc;
			border-right: 1px solid #ccc;
			border-bottom: 2px solid #c00;
			background: #dcdcd1;
			text-align : center;
		}
		table.type08 tbody th {
			width: 150px;
			padding: 10px;
			font-weight: bold;
			vertical-align: top;
			border-right: 1px solid #ccc;
			border-bottom: 1px solid #ccc;
			background: #ececec;
			text-align : center;
		}
		table.type08 td {
			width: 350px;
			padding: 10px;
			vertical-align: top;
			border-right: 1px solid #ccc;
			border-bottom: 1px solid #ccc;
		}
	</style>
	</head>
	<body>

		<!-- Header -->
			<header id="header" class="alt">
				<div class="inner">
					<h1>IOT 어촌편</h1>
					<p>현성 종인 프로젝트</p>
				</div>
			</header>

		<!-- Wrapper -->
			<div id="wrapper">

				<!-- Banner -->
					<section id="intro" class="main">
						<span class="icon fa-diamond major"></span>
						<h2> 프로젝트설명</h2>
						<p> 어촌 생활이 익숙하지 않은 분들을 위한 가이드</p>
					<div class = "spec">
						<table class="type08">
						<thead>
							<tr>
								<th scope="cols">항목</th>
								<th scope="cols">파도 세기</th>
							<th scope="cols">수위 체크</th>

							</tr>
						</thead>
							<tbody>
							<tr>
								<th scope="row">상</th>
								<td> 20 이상(위험)</td> 
								<td> 밀 물(60이상)</td>
							</tr>
							<tr>
								<th scope="row">중</th>
								<td> 10 초과 <br>
									 20 이하(애매)
								</td>
								<td> 밀 물 -> 썰 물 <br>
									 썰 물 -> 밀 물 
								</td>
							</tr>
							<tr>
								<th scope="row">하</th>
								<td> 10 이하(적당)</td>
								<td> 썰 물(20이하) </td>
							</tr>
							</tbody>
						</table>
					</div>
					<h2> 현 재 위 치</h2>
					<div id="map" style="width:100%;height:400px;"></div>

					</section>

				<!-- Items -->
					<section class="main items">
						<article class="item">
							<header>
								<!--
								<a href="#"><img src="images/pic01.jpg" alt="" /></a>
								<h3>Feugiat et faucibus</h3>
								-->
								<div id="chart_div"></div>
							</header>
							<p><b><전체 데이터 그래프></b><br><br>
								한 번에 측정 데이터를 볼 수 있는 그래프 
							
							</p>
							<!-- 
							<ul class="actions">
								<li><a href="#" class="button">More</a></li>
							</ul>
							-->
						</article>
						<article class="item">
							<header>
								<!--
								<a href="#"><img src="images/pic02.jpg" alt="" /></a>
								<h3>Blandit adipiscing</h3>
								-->
								<div id="chart_div1"></div>
							</header>
							<p> <b><온도 습도 조도></b> <br><br>
								조도값 : 0 ~ 1023 수치 MAP함수 이용<br>
								0 ~ 100 % 단위로 측정

							</p>
							<!--
							<ul class="actions">
								<li><a href="#" class="button">More</a></li>
							</ul>
							-->
						</article>
						<article class="item">
							<header>
								<!--
								<a href="#"><img src="images/pic03.jpg" alt="" /></a>
								<h3>Lorem massa nulla</h3>
								-->
								<div id="chart_div2"></div>
							</header>
							<p> <b><파 도 세 기></b> <br><br>
								1초 동안 기울기 변화가<br>
								얼마나 있었는 지에 대한  카운팅
							</p>
							<!--
							<ul class="actions">
								<li><a href="#" class="button">More</a></li>
							</ul>
							-->
						</article>
						<article class="item">
							<header>
								<!--
								<a href="#"><img src="images/pic04.jpg" alt="" /></a>
								<h3>Ipsum sed tempus</h3>
								-->
								<div id="chart_div3"></div>
							</header>
							<p> <b><수 위></b> <br><br>
								0 ~ 950 의 수치를 MAP함수 이용<br> 
								0 ~ 100 % 단위로 측정
							</p>
							 <!--
							 <ul class="actions">
								<li><a href="#" class="button">More</a></li>
							</ul>
							-->
						</article>
					</section>

				<!-- CTA -->
					<section id="cta" class="main special">
						<h2>사 용 센 서</h2>
					<div class ="container">
					<div class ="row">
						<div class = "col-3">
						<div clas="card">
							<img src="images/dhtsensor.png" alt="" width="250" height="200" />
							<div class= "container">
							<p> DHT Sensor </p>
							</div>
						</div>
						</div>

						<div class = "col-3">
						<div clas="card">
								<img src="images/cdssensor.jpg" alt="" width="250" height="200" />
							<div class= "container">
							<p> CDS Sensor </p>
							</div>
						</div>
						</div>

						<div class = "col-3">
						<div clas="card">
							<img src="images/tiltsensor.jpg" alt="" width="250" height="200"/>
							<div class= "container">
							<p> Tilt Sensor </p>
							</div>
						</div>
						</div>

						<div class = "col-3">
						 <div clas="card">
							<img src="images/water_level_sensor.jpg" alt="" width="250" height="200" />
							<div class= "container">
							<p> Water Level Sensor </p>
							</div>
						</div>
						</div>
						</div>
					</div>
					<h2> 사 용 장 비 </h2>
					<div class ="container">
						<div class ="row">
                                                <div class = "col-6">
                                                <div clas="card">
                                                        <img src="images/arduino.png" alt="" width="250" height="200" />
                                                        <div class= "container">
                                                        <p> Arduino </p>
                                                        </div>
                                                </div>
                                                </div>

                                                <div class = "col-6">
                                                <div clas="card">
                                                                <img src="images/raspberry.jpg" alt="" width="250" height="200" />
                                                        <div class= "container">
                                                        <p> Raspberry Pi </p>
                                                        </div>
                                                </div>
                                                </div>

											</div>
                                        </div>

						<ul class="actions">
							<li><a href="#" class="button big">맨 위 로</a></li>
						</ul>
					</section>

				<!-- Main -->
				<!--
					<section id="main" class="main">
						<header>
							<h2>Lorem ipsum dolor</h2>
						</header>
						<p>Fusce malesuada efficitur venenatis. Pellentesque tempor leo sed massa hendrerit hendrerit. In sed feugiat est, eu congue elit. Ut porta magna vel felis sodales vulputate. Donec faucibus dapibus lacus non ornare. Etiam eget neque id metus gravida tristique ac quis erat. Aenean quis aliquet sem. Ut ut elementum sem. Suspendisse eleifend ut est non dapibus. Nulla porta, neque quis pretium sagittis, tortor lacus elementum metus, in imperdiet ante lorem vitae ipsum. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Etiam eget neque id metus gravida tristique ac quis erat. Aenean quis aliquet sem. Ut ut elementum sem. Suspendisse eleifend ut est non dapibus. Nulla porta, neque quis pretium sagittis, tortor lacus elementum metus, in imperdiet ante lorem vitae ipsum. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.</p>
					</section>
				-->

				<!-- Footer -->
					<footer id="footer">
						<ul class="icons">
							<li><a href="#" class="icon fa-twitter"><span class="label">Twitter</span></a></li>
							<li><a href="#" class="icon fa-facebook"><span class="label">Facebook</span></a></li>
							<li><a href="#" class="icon fa-instagram"><span class="label">Instagram</span></a></li>
							<li><a href="#" class="icon fa-linkedin"><span class="label">LinkedIn</span></a></li>
							<li><a href="#" class="icon fa-envelope"><span class="label">Email</span></a></li>
						</ul>
						<p class="copyright">&copy; IOT 어촌편. Made By: 현성 종인.</p>
					</footer>

			</div>
		<!-- PHP -->
		<?php
			$conn = mysqli_connect("localhost", "emb", "kcci");
			mysqli_set_charset($conn, "utf8");

			mysqli_select_db($conn, "test");
			
			$result = mysqli_query($conn, "select left(time,5), temperature, moisture, water_level, wave_cnt, cds from sensing");
			$result1 = mysqli_query($conn, "select left(time,5), temperature, moisture, cds from sensing");
			$result2 = mysqli_query($conn, "select left(time,5), wave_cnt from sensing");
			$result3 = mysqli_query($conn, "select left(time,5), water_level from sensing");

			$data = array(array('시 간', '온 도', '습 도','수 위','파도세기','조 도'));
			$data1 = array(array('시 간', '온 도', '습 도' ,'조 도'));
			$data2 = array(array('시 간', '파도세기'));
			$data3 = array(array('시 간', '수 위'));
			
			if( $result)
			{
				while($row = mysqli_fetch_array($result))
				{
					array_push($data, array( $row[0], intval($row[1]), intval($row[2]), intval($row[3]), intval($row[4]), intval($row[5]) ) );
				}
			}
			if( $result1)
			{
				while($row = mysqli_fetch_array($result1))
				{
					array_push($data1, array( $row[0], intval($row[1]), intval($row[2]),intval($row[3]) ));
				}
			}
			if( $result2)
			{
				while($row = mysqli_fetch_array($result2))
				{
					array_push($data2, array( $row[0], intval($row[1])));
				}
			}
			if( $result3)
			{
				while($row = mysqli_fetch_array($result3))
				{
					array_push($data3, array( $row[0], intval($row[1]) ));
				}
			}
			$options = array(
				'title' => '시간 별 값',
				'width' => 660, 'height' => 310
			);
		?>
		<!-- Scripts -->
			<script src="assets/js/jquery.min.js"></script>
			<script src="assets/js/skel.min.js"></script>
			<script src="assets/js/util.js"></script>
			<script src="assets/js/main.js"></script>
			<script src="//www.google.com/jsapi"></script>
			<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js"></script>
			<script type="text/javascript" src="//dapi.kakao.com/v2/maps/sdk.js?appkey=38ad22c22a81cb2df106c0206ea0a674"></script>
			//<script type="text/javascript" src="//dapi.kakao.com/v2/maps/sdk.js?appkey=1a3a90ac8f10a3c650a1eae48286239f"></script>
		<script>
		window.onload = function(){
		if(navigator.geolocation == undefined) {
			alert('본 기기가 위치 정보를 지원하지 않습니다.');
			return;
		}
		//var lat;
		//var lon;

		navigator.geolocation.getCurrentPosition(function(pos){
			lat = pos.coords.latitude;
			lon = pos.coords.longitude;
			make_map(lat,lon);

		});

		//위도,경도값 호출이 가능한 경우
		/*
		function success(position) {
			latitude : 위도
			longitude : 경도
			altitude : 고도
			accuracy : 위도와 경도의 정확도
			altitudeAccuracy : 고도의 정확도
			heading : 방향(북쪽으로부터 시계방향으로 현재 방향까지의 각도)
			speed : 현재 기기의 속도를 meter per second
			lat = position.coords.latitude;
			lon = position.coords.longitude;
		}
		alert("lat : " + lat + "lon:" + lon);
		//위도,경도값 호출이 불가능한 경우
		/*
		function fail(error) {
			alert('에러 발생 코드 : ' + error.code);
			0 : 알 수 없는 오류
			1 : 권한 거부
			2 : 위치 추적 실패
			3 : 시간 초과
		}
		*/
		function make_map( lat, lon)
		{
		var container = document.getElementById('map');
		var options = {
			center: new kakao.maps.LatLng(lat, lon),
			level: 3
		};

		var map = new kakao.maps.Map(container, options);
	 	var markerposition = new kakao.maps.LatLng(lat,lon);

		var marker = new kakao.maps.Marker({
			position : markerposition
		});
		marker.setMap(map);
		}
		
	};

		var data = <?= json_encode($data) ?>;
		var data1 = <?= json_encode($data1) ?>;
		var data2 = <?= json_encode($data2) ?>;
		var data3 = <?= json_encode($data3) ?>;
		var options = <?= json_encode($options) ?>;
		google.load('visualization', '1.0', {'packages':['corechart']});
		google.setOnLoadCallback(function() {
			var chart = new google.visualization.LineChart(document.querySelector('#chart_div'));
			var chart1 = new google.visualization.LineChart(document.querySelector('#chart_div1'));
			var chart2 = new google.visualization.LineChart(document.querySelector('#chart_div2'));
			var chart3 = new google.visualization.LineChart(document.querySelector('#chart_div3'));
		  chart.draw(google.visualization.arrayToDataTable(data), options);
		  chart1.draw(google.visualization.arrayToDataTable(data1), options);
		  chart2.draw(google.visualization.arrayToDataTable(data2), options);
		  chart3.draw(google.visualization.arrayToDataTable(data3), options);
		});
		</script>

	</body>
</html>

