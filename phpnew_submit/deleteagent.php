<!DOCTYPE html>
<html>
<head>
  <meta charset = 'UTF-8'>
  <title>Delete Agent</title>
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
  
if(!($stmt = $mysqli->prepare("DELETE FROM agent WHERE id = ?"))){
  echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("i",$_POST['agent_id']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
}
else {
	echo "Deleted " . $stmt->affected_rows . " rows from agent.";
}
?>

<p><a href="home.php">back to main menu</a></p>

</body>
</html>