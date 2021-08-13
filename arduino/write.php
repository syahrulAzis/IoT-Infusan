<?php
include("../db/koneksi.php");
// $temp = $_GET['suhu'];
// $humi = $_GET['kelembaban'];
$brt  = $_GET['berat'];
//$ppm = $_GET['gas'];

//$simpan = mysqli_query($konek, "INSERT INTO `work` (`suhu`, `kelembaban`,`cahaya`,`gas`) VALUES ($temp, $humi,$ldr,$ppm)");
$simpan = mysqli_query($konek, "INSERT INTO `timbangan` (`berat`) VALUES ($brt)");

//$simpan = mysqli_query($konek, "UPDATE timbangan SET berat='$brt'");

//Notofikasi Bila Data Tersimpan
if ($simpan) {
    echo "Data Berhasil disimpan";
} else {
    echo "Data Gagal disimpan";
}
