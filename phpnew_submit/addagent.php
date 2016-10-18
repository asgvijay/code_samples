<!DOCTYPE html>
<html>
<head>
  <meta charset = 'UTF-8'>
  <title>Add Agent</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>

<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","changal-db","0YPDXXxnCp1uIvgn","changal-db");
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
  
if(!($stmt = $mysqli->prepare("INSERT INTO agent (first_name, last_name, email) VALUES (?,?,?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("sss",$_POST['first_name'],$_POST['last_name'],$_POST['email']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
}
else {
	echo "Added " . $stmt->affected_rows . " rows to agent.";
}
?>

<p><a href="home.php">back to main menu</a></p>

</body>
</html>