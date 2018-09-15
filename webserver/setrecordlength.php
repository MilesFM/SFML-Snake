<?php

$filename = "recordlength.txt";

if (!empty($_POST["newrecordlength"])) {
    $recordlengthfileread = fopen($filename, "r");
    $line = fgets($recordlengthfileread);
    if ((int)$_POST["newrecordlength"] > (int)$line) {
        $recordlengthfilewrite = fopen($filename , "w");
        fwrite($recordlengthfilewrite, $_POST["newrecordlength"]);
        fclose($recordlengthfilewrite);
    }
    fclose($recordlengthfileread);
}

?>