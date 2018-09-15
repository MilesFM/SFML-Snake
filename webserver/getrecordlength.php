<?php

$filename = "recordlength.txt";
$recordlengthfile = fopen($filename, "r");
$line = fgets($recordlengthfile);
echo $line;

?>