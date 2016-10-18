<!DOCTYPE html>
<html>
<head>
  <meta charset = 'UTF-8'>
  <title>Add House</title>
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
  
if(!($stmt = $mysqli->prepare("INSERT INTO house(street_number, street_name, zip_code, city_id, agent_id, listing_id) VALUES (?, ?, ?, ?, ?, ?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("ssiiii",$_POST['street_number'],$_POST['street_name'],$_POST['zip_code'],$_POST['city'],$_POST['agent'],$_POST['listing']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
}
else {
	echo "Added " . $stmt->affected_rows . " rows to house.";
}
?>

<p><a href="home.php">back to main menu</a></p>

</body>
</html>