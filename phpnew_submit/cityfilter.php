<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","changal-db","0YPDXXxnCp1uIvgn","changal-db");
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>
<!DOCTYPE html>
<html>
<head>
	<meta charset = 'UTF-8'>
	<title>City Filter</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
				
        
<div>
  <h3>House Listing - By City</h3>
  <p>While city name and crime rate won't change here (filtering by city) the city name and crime rate is included in the table.</p>
	<table>
  <thead>
		<tr>
			<th>Address</th>
			<th>City</th>
      <th>Crime Rate</th>
			<th>ZIP</th>
      <th>Listing</th>
      <th>Agent</th>
      <th>Agent e-mail</th>
		</tr>
    </thead>
    <tbody>
<?php
if(!($stmt = $mysqli->prepare("SELECT street_number, street_name, city.name, state, crime_rate, zip_code, listing.type, first_name, last_name, email FROM house INNER JOIN city ON house.city_id = city.id LEFT JOIN agent ON house.agent_id = agent.id LEFT JOIN listing ON house.listing_id = listing.id WHERE city.id = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!($stmt->bind_param("i",$_POST['City']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($street_number , $street_name , $city_name, $state, $crime, $zip, $listing_type, $first_name, $last_name, $email )){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $street_number . " " . $street_name . "\n</td>\n<td>\n" . $city_name . " " . $state . "\n</td>\n<td>\n" . $crime . "\n</td>\n<td>\n" . $zip . "\n</td>\n<td>\n" . $listing_type . "\n</td>\n<td>\n" . $first_name . " " . $last_name . "\n</td>\n<td>\n" . $email . "\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>

<p><a href="home.php">back to main menu</a></p>

</body>
</html>

