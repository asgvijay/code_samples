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
  <title>House Filter</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
        
        
<div>
  <h3>School Listing - By House</h3>
  <table>
  <thead>
    <tr>
      <th>Address</th>
      <th>City</th>
      <th>ZIP</th>
      <th>School</th>
            <th>School Type</th>
            <th>School Rating</th>
    </tr>
    </thead>
    <tbody>
<?php
if(!($stmt = $mysqli->prepare("SELECT street_number, street_name, city.name, state, zip_code, school.name, school.type, school.rating FROM house LEFT JOIN city ON house.city_id = city.id INNER JOIN house_school ON house.id = house_school.house_id INNER JOIN school ON house_school.school_id = school.id WHERE house.id = ?"))){
  echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!($stmt->bind_param("i",$_POST['house_id']))){
  echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
  echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($street_number , $street_name , $city_name, $state, $zip, $school_name, $school_type, $school_rating)){
  echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $street_number . " " . $street_name . "\n</td>\n<td>\n" . $city_name . " " . $state . "\n</td>\n<td>\n" . $zip . "\n</td>\n<td>\n" . $school_name . "\n</td><td>\n" . $school_type . "\n</td><td>\n" . $school_rating . "\n</td></tr>";
}
$stmt->close();
?>
  </table>
</div>

<p><a href="home.php">back to main menu</a></p>

</body>
</html>

