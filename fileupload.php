<?php
if(isset($_FILES["filetoupload"]))
{
	$path="C:/xampp/htdocs/";
	$path=$path.basename($_FILES['filetoupload']['name']);
	print($path);
	if(move_uploaded_file($_FILES['filetoupload']['tmp_name'],$path))
	{
		print("upload success");
	}
	else
	{
		print("no success");
		
	}
	
}


?>

<html>
<body>
<form action="fileupload.php" method="post" enctype="multipart/form-data">  
    Select File:  
    <input type="file" name="filetoupload"/>  
    <input type="submit" value="Upload Image" name="submit"/>  
</form>  
</body>
</html>