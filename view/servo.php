<?php
include "../db/koneksi.php";

$pos = $_GET['pos'];

mysqli_query($konek, "UPDATE tb_kontrol SET servo='$pos'");

echo $pos;
