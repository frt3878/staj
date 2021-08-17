const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
	<meta charset='utf-8'>
	<title>Kontrol Paneli</title>
    <link href='https://cdn.jsdelivr.net/npm/bootstrap@5.1.0/dist/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-KyZXEAg3QhqLMpG8r+8fhAXLRk2vvoC2f3B09zVXn8CA5QIVfZOJ3BCsw2P0p/We' crossorigin='anonymous'>
  </head>
<style type="text/css">
.button {
  background-color: #4CAF50; /* Green */
  border: none;
  color: white;
  padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
}
</style>
<body style="background-color: #f9e79f ">

<center>
<div>
<img src='https://www.yenibiris.com/logo/41985.jpg' class='rounded mx-auto d-block' alt='...'>
<h2>Sıcaklık Kontrol Terminali</h2>
  <button class="button" onclick="send(1)">LED ON</button>
  <button class="button" onclick="send(0)">LED OFF</button><BR>
</div>
 <br>
<div><h4>
  Temp(C): <span id="adc_val">0</span> &nbsp;&nbsp;&nbsp;
  LED State: <span id="state">NA</span>
</h4>
</div>
    <div id='wrapper'>
      <div id='content-wrapper' class='d-flex flex-column'>
        <div id='content'>
          
          <div class='container-fluid' id='container-wrapper'>
            <div class='d-sm-flex align-items-center justify-content-between mb-4'></div>
            <div class='row'>
              <div class='col-lg-12'>
                <div class='card mb-4'>
                  <div class='card-header py-3 d-flex flex-row align-items-center justify-content-between'>
                    <h6 class='m-0 font-weight-bold text-primary'>Son 10 dakikalık sıcaklık verisi</h6>
                  </div>
                  <div class='card-body'>
                    <div class='chart-area'>
                      <canvas id='myAreaChart'></canvas>
                    </div>
                    <hr>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
<script src='https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.4.0/Chart.min.js'></script>
    <script>
      function number_format(number, decimals, dec_point, thousands_sep) {
        number = (number + '').replace(',', '').replace(' ', '');
        var n = !isFinite(+number) ? 0 : +number,
          prec = !isFinite(+decimals) ? 0 : Math.abs(decimals),
          sep = (typeof thousands_sep === 'undefined') ? ',' : thousands_sep,
          dec = (typeof dec_point === 'undefined') ? '.' : dec_point,
          s = '',
          toFixedFix = function(n, prec) {
            var k = Math.pow(10, prec);
            return '' + Math.round(n * k) / k;
          };
        s = (prec ? toFixedFix(n, prec) : '' + Math.round(n)).split('.');
        if (s[0].length > 3) {
          s[0] = s[0].replace(/\B(?=(?:\d{3})+(?!\d))/g, sep);
        }
        if ((s[1] || '').length < prec) {
          s[1] = s[1] || '';
          s[1] += new Array(prec - s[1].length + 1).join('0');
        }
        return s.join(dec);
      }
      var ctx = document.getElementById('myAreaChart');
      var myLineChart = new Chart(ctx, {
        type: 'line',
        data: {
          labels: ['-10 min', '-9 min', '-8 min', '-7 min', '-6 min', '-5 min', '-4 min', '-3 min', '-2 min', '-1 min', 'Now'],
          datasets: [{
            label: 'Sıcaklık',
            lineTension: 0.3,
            backgroundColor: 'rgba(78, 115, 223, 0.5)',
            borderColor: 'rgba(78, 115, 223, 1)',
            pointRadius: 3,
            pointBackgroundColor: 'rgba(78, 115, 223, 1)',
            pointBorderColor: 'rgba(78, 115, 223, 1)',
            pointHoverRadius: 3,
            pointHoverBackgroundColor: 'rgba(78, 115, 223, 1)',
            pointHoverBorderColor: 'rgba(78, 115, 223, 1)',
            pointHitRadius: 10,
            pointBorderWidth: 2,
            data: [null, null, null, null, null, null, null, null, null, null],
          }],
        },
        options: {
          responsive: true,
          maintainAspectRatio: false,
          layout: {
            padding: {
              left: 10,
              right: 25,
              top: 25,
              bottom: 0
            }
          },
          scales: {
            xAxes: [{
              time: {
                unit: 'date'
              },
              gridLines: {
                display: false,
                drawBorder: false
              },
              ticks: {
                maxTicksLimit: 7
              }
            }],
            yAxes: [{
              ticks: {
                maxTicksLimit: 5,
                padding: 10,
                callback: function(value, index, values) {
                  return number_format(value) + ' C°';
                }
              },
              gridLines: {
                color: 'rgb(234, 236, 244)',
                zeroLineColor: 'rgb(234, 236, 244)',
                drawBorder: false,
                borderDash: [2],
                zeroLineBorderDash: [2]
              }
            }],
          },
          legend: {
            display: false
          },
          tooltips: {
            backgroundColor: 'rgb(255,255,255)',
            bodyFontColor: '#858796',
            titleMarginBottom: 10,
            titleFontColor: '#6e707e',
            titleFontSize: 14,
            borderColor: '#dddfeb',
            borderWidth: 1,
            xPadding: 15,
            yPadding: 15,
            displayColors: false,
            intersect: false,
            mode: 'index',
            caretPadding: 10,
            callbacks: {
              label: function(tooltipItem, chart) {
                var datasetLabel = chart.datasets[tooltipItem.datasetIndex].label || '';
                return datasetLabel + ' ' + number_format(tooltipItem.yLabel) + ' C°';
              }
            }
          }
        }
      });

      
        
      
      
    </script>
<script>
function send(led_sts) 
{
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("state").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "led_set?state="+led_sts, true);
  xhttp.send();
}
setInterval(function() 
{
  getData();
}, 1000); 
setInterval(function() 
{
  getData2();
}, 30000); 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("adc_val").innerHTML =
      this.responseText;
	  
	  
    }
  };
  xhttp.open("GET", "adcread", true);
  xhttp.send();
}
function getData2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      
	  
	  if (myLineChart.config.data.datasets[0].data.length >= 11) myLineChart.config.data.datasets[0].data.shift();
        myLineChart.config.data.datasets[0].data.push(this.responseText);
        myLineChart.update();
    }
  };
  xhttp.open("GET", "adcread", true);
  xhttp.send();
}
</script>
</center>
<a href="http://www.yesilotomasyon.com.tr/bize-ulasin/" target="_blank">Bize Ulasın</a>
</body>
</html>
)=====";
