<?php
class kondisiTaman{
 public $link='';
 function __construct($humidityData1, $humidityData2, $temperatureData1, $temperatureData2, $cahaya){
  $this->connect();
  $this->storeInDB($humidityData1, $humidityData2, $temperatureData1, $temperatureData2, $cahaya);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'mikrokontroler') or die('Cannot select the DB');
 }
 
 function storeInDB($humidityData1, $humidityData2, $temperatureData1, $temperatureData2, $cahaya){
  $query = "insert into kondisiTaman set humidity_selatan='".$humidityData1."', humidity_utara='".$humidityData2."', temperature_selatan='".$temperatureData1."', temperature_utara='".$temperatureData2."', cahaya_tengah='".$cahaya."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}

if($_GET['humidityData1'] != '' and  $_GET['humidityData2'] != '' and  $_GET['temperatureData1'] != '' and  $_GET['temperatureData2'] != '' and  $_GET['cahaya'] != ''){
 $kondisiTaman=new kondisiTaman($_GET['humidityData1'],$_GET['humidityData2'],$_GET['temperatureData1'],$_GET['temperatureData2'],$_GET['cahaya']);
}
?>