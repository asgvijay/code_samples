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
  <title>Editing house</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>

<h3>Current House information</h3>
<table>
<thead>
  <tr>
    <th>Address</th>
    <th>City</th>
    <th>ZIP</th>
    <th>Listing</th>
    <th>Agent</th>
    <th>Agent e-mail</th>
  </tr>
  </thead>
  <tbody>
<?php
if(!($stmt = $mysqli->prepare("SELECT house.id, street_number, street_name, city.name, state, zip_code, listing.type, first_name, last_name, email FROM house LEFT JOIN city ON house.city_id = city.id LEFT JOIN agent ON house.agent_id = agent.id LEFT JOIN listing ON house.listing_id = listing.id WHERE house.id = ?"))){
  echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!($stmt->bind_param("i",$_POST['house_id']))){
  echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
  echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $street_num, $street_name, $city_name, $state, $zip, $listing_type, $first_name, $last_name, $email)){
  echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $street_num . " " . $street_name . "\n</td>\n<td>\n" . $city_name . " " . $state . "\n</td>\n<td>\n" . $zip . "\n</td>\n<td>\n" . $listing_type . "\n</td>\n<td>\n" . $first_name . " " . $last_name . "\n</td>\n<td>\n" . $email . "\n</td>\n</tr>";
}
//Not closed yet, hold on.
?>
  </tbody>
</table>
<p>If you wish to keep the same values, feel free to copy and paste it from this short table. If you want to null out a value, too bad.</p>
</div>

<div>
  <form method="post" action="updatehouse.php"> 
    <fieldset>
      <legend>Enter this house's new information</legend>
      <p>Street Number: <input type="text" name="street_number" /></p>
      <p>Street Name : <input type="text" name="street_name" /></p>
      <p>Zip Code : <input type="number" name="zip_code" /></p>    
      <label>City</label>
<?php
echo '<input type="hidden" name = "house_id" value = ' . $id . '>';
$stmt->close();
//Now it's closed.
?>

      <select name="city">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, name, state FROM city"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $cname, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
    echo '<option value=" '. $id . ' "> ' . $cname . " " . $state . '</option>\n'; // check variable names
}
$stmt->close();
?>
      </select>
      <br>                     
      <label>Agent</label>
      <select name="agent">
<?php
if(!($stmt1 = $mysqli->prepare("SELECT id, first_name, last_name FROM agent"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt1->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt1->bind_result($id, $fname, $lname)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt1->fetch()){
    echo '<option value=" '. $id . ' "> ' . $fname . " " . $lname . '</option>\n';
}
$stmt1->close();
?>
      </select>
      <br>
      <label>Listing Type</label>
      <select name="listing">
<?php
if(!($stmt2 = $mysqli->prepare("SELECT id, type FROM listing"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt2->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt2->bind_result($id, $type)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt2->fetch()){
    echo '<option value=" '. $id . ' "> ' . $type . '</option>\n';
}
$stmt2->close();
?>
      </select>
      <p><input type="submit" /></p>
    </fieldset>
  </form>
</div>

<p><a href="home.php">back to main menu</a></p>

</body>
</html>