<?php
include("../db/get_data.php");
$data = data('berat');
if($data<=500&&$data>=250){
    echo "<font color='green'>Infusan Penuh</font><br>";
}else if($data<=250&&$data>=10){
    echo "<font color='blue'>Infusan Sedang</font><br>";
}else if($data<=10&&$data>=1){
    echo "<font color='Red'>Infusan Hampir Habis</font><br>";
}

//echo data('berat') . " Gram";
// mysqli_close($konek);
