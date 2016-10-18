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
	<title>Main menu</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
				
        
<div>
  <h3>House Listing</h3>
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
if(!($stmt = $mysqli->prepare("SELECT street_number, street_name, city.name, state, zip_code, listing.type, first_name, last_name, email FROM house LEFT JOIN city ON house.city_id = city.id LEFT JOIN agent ON house.agent_id = agent.id LEFT JOIN listing ON house.listing_id = listing.id"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($street_num, $street_name, $city_name, $state, $zip, $listing_type, $first_name, $last_name, $email)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>" . $street_num . " " . $street_name . "</td>\n<td>" . $city_name . " " . $state . "</td>\n<td>" . $zip . "</td>\n<td>" . $listing_type . "</td>\n<td>" . $first_name . " " . $last_name . "</td>\n<td>" . $email . "</td>\n</tr>";
}
$stmt->close();
?>
  </tbody>
  </table>
</div>

<div>
  <h3>School Listing (with School Ratings)</h3>
  <p>For rating, higher is better.</p>
  <table>
  <thead>
    <tr>
      <th>School Name</th>
      <th>School Type</th>
      <th>School Rating</th>
    </tr>
    </thead>
    <tbody>
<?php
if(!($stmt = $mysqli->prepare("SELECT name, type, rating FROM school"))){
  echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
  echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($school_name, $school_type, $school_rating)){
  echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>" . $school_name . "</td>\n<td>" . $school_type . "</td>\n<td>" . $school_rating . "</td>\n</tr>";
}
$stmt->close();
?>
  </tbody>
  </table>
</div>

<div>
  <h3>City Listing (with Crime Rates)</h3>
  <p>For crime rate, lower is better (safer).</p>
  <table>
  <thead>
    <tr>
      <th>City</th>
      <th>Crime Rate</th>
    </tr>
    </thead>
    <tbody>
<?php
if(!($stmt = $mysqli->prepare("SELECT name, state, crime_rate FROM city"))){
  echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
  echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($city_name, $state, $crime)){
  echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>" . $city_name . " " . $state . "</td>\n<td>" . $crime . "</td>\n</tr>";
}
$stmt->close();
?>
  </tbody>
  </table>
</div>

<div>
  <h3>Agent Listing</h3>
  <p>This table is just here in case there are agents who aren't attached to houses at the moment. They are out of work, but not forgotten.</p>
  <table>
  <thead>
    <tr>
      <th>Name</th>
      <th>e-mail</th>
    </tr>
    </thead>
    <tbody>
<?php
if(!($stmt = $mysqli->prepare("SELECT first_name, last_name, email FROM agent"))){
  echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
  echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($f_name, $l_name, $email)){
  echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>" . $f_name . " " . $l_name . "</td>\n<td>" . $email . "</td>\n</tr>";
}
$stmt->close();
?>
  </tbody>
  </table>
</div>

<fieldset>
<legend>Filtering</legend>
<p>These filters should fulfill the search requirement, but we use drop-downs instead of text-fields. Drop-downs help to prevent mistakes.</p>
   <div>
	<form method="post" action="cityfilter.php">
		<fieldset>
			<legend>Filter Houses By City</legend>
				<select name="City">
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
    <input type="submit" value="Run Filter" />
		</fieldset>
	</form>
</div>
    
   <div>
	<form method="post" action="schoolfilter.php">
		<fieldset>
			<legend>Filter Houses By School</legend>
				<select name="School">
<?php
if(!($stmt1 = $mysqli->prepare("SELECT school.id, school.name, city.name, state FROM school LEFT JOIN city ON school.city_id = city.id"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt1->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt1->bind_result($id, $name, $city, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt1->fetch()){
    echo '<option value=" '. $id . ' "> ' . $name . ", " . $city . " " . $state . '</option>\n';
}
$stmt1->close();
?>
				</select>
        <br>
    <input type="submit" value="Run Filter" />
		</fieldset>
	</form>
</div>

   <div>
  <form method="post" action="schoolfilter-reverse.php">
    <fieldset>
      <legend>Filter Schools By House</legend>
      <p>This is the reverse operation of the previous filter.</p>
        <select name="house_id">
<?php
if(!($stmt = $mysqli->prepare("SELECT house.id, street_number, street_name, zip_code, name, state FROM house LEFT JOIN city ON house.city_id = city.id"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $number, $name, $zip, $city_name, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
    echo '<option value=" '. $id . ' "> ' . $number . " " . $name . ", " . $city_name . " " . $state . " " . $zip . '</option>\n';
}
?>
        </select>
        <br>
    <input type="submit" value="Run Filter" />
    </fieldset>
  </form>

</fieldset>
        
<div>
<fieldset>
<legend>Data Adjustment</legend>

  <div>
    <form method="post" action="addhouse-basic.php"> 
      <fieldset>
        <legend>Add House (basic info only)</legend>
        <p>Street Number: <input type="text" name="street_number" /></p>
        <p>Street Name : <input type="text" name="street_name" /></p>
        <p>Zip Code : <input type="number" name="zip_code" /></p>
        <p><input type="submit" /></p>
      </fieldset>
    </form>
  </div>

  <div>
    <form method="post" action="addhouse.php"> 
      <fieldset>
        <legend>Add House (full info)</legend>
        <p>Street Number: <input type="text" name="street_number" /></p>
        <p>Street Name : <input type="text" name="street_name" /></p>
        <p>Zip Code : <input type="number" name="zip_code" /></p>    
        <label>City</label>
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

  <div>
    <form method="post" action="edithouse.php"> 
      <fieldset>
        <legend>Edit House Information</legend> 
        <label>Address</label>
        <select name="house_id">
<?php
if(!($stmt = $mysqli->prepare("SELECT house.id, street_number, street_name, zip_code, name, state FROM house LEFT JOIN city ON house.city_id = city.id"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $number, $name, $zip, $city_name, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
    echo '<option value=" '. $id . ' "> ' . $number . " " . $name . ", " . $city_name . " " . $state . " " . $zip . '</option>\n';
}
$stmt->close();
?>
        </select>
        <p><button type="submit">edit this house</button></p>
      </fieldset>
    </form>
  </div>

  <div>
    <form method="post" action="deletehouse.php"> 
      <fieldset>
        <legend>Delete House</legend> 
        <label>Address</label>
        <select name="house_id">
<?php
if(!($stmt = $mysqli->prepare("SELECT house.id, street_number, street_name, zip_code, name, state FROM house LEFT JOIN city ON house.city_id = city.id"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $number, $name, $zip, $city_name, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
    echo '<option value=" '. $id . ' "> ' . $number . " " . $name . ", " . $city_name . " " . $state . " " . $zip . '</option>\n';
}
$stmt->close();
?>
        </select>
        <p><button type="submit">delete this house</button></p>
      </fieldset>
    </form>
  </div>

  <div>
    <form method="post" action="addlisting.php"> 
      <fieldset>
        <legend>Add Listing Type</legend> 
        <p>Please check the existing listing types before adding a new one. (There's a convenient drop-down list in the form for deleting listing types.)</p>
        <p>New type: <input type="text" name="listing" /></p>
        <p><button type="submit">add</button></p>
      </fieldset>
    </form>
  </div>

  <div>
    <form method="post" action="deletelisting.php"> 
      <fieldset>
        <legend>Delete Listing Type</legend> 
        <select name="listing_id">
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
        <p><button type="submit">delete</button></p>
      </fieldset>
    </form>
  </div>

  <div>
    <form method="post" action="addcity.php"> 
      <fieldset>
        <legend>Add City</legend> 
        <p>Please check the existing cities before adding a new one. (There's a convenient drop-down list in the form for deleting cities.)</p>
        <p>City: <input type="text" name="city" /></p>
        <p>State (two-letter code): <input type="text" name="state" /></p>
          <p>Crime Rating: <input type="text" name="crime" /></p>
        <p><button type="submit">add</button></p>
      </fieldset>
    </form>
  </div>
    
  <div>
    <form method="post" action="deletecity.php"> 
      <fieldset>
        <legend>Delete City</legend> 
        <select name="city_id">
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
        <p><button type="submit">delete</button></p>
      </fieldset>
    </form>
  </div>
    
  <div>
    <form method="post" action="addagent.php"> 
      <fieldset>
        <legend>Add Agent</legend> 
        <p>Please check the existing agents before adding a new one. (There's a convenient drop-down list in the form for deleting agents.)</p>
        <p>First Name: <input type="text" name="first_name" /></p>
        <p>Last Name:  <input type="text" name="last_name" /></p>
        <p>Email:  <input type="text" name="email" /></p>
        <p><button type="submit">add</button></p>
      </fieldset>
    </form>
  </div>  

  <div>
    <form method="post" action="deleteagent.php"> 
      <fieldset>
        <legend>Delete Agent</legend> 
        <select name="agent_id">
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
        <p><button type="submit">delete</button></p>
      </fieldset>
    </form>
  </div>

  <div>
    <form method="post" action="addschool.php"> 
      <fieldset>
        <legend>Add School</legend> 
        <p>Please check the existing schools before adding a new one. (There's a convenient drop-down list in the form for deleting schools.)</p>
        <p>Name: <input type="text" name="name" /></p>
        <p>Type:  <input type="text" name="type" /></p>
        <p>Rating:  <input type="number" name="rating" /></p>
        <select name="city_id">
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
        <p><button type="submit">add</button></p>
      </fieldset>
    </form>
  </div>  

  <div>
    <form method="post" action="deleteschool.php"> 
      <fieldset>
        <legend>Delete School</legend> 
        <select name="school_id">
<?php
if(!($stmt1 = $mysqli->prepare("SELECT school.id, school.name, city.name, state FROM school LEFT JOIN city ON school.city_id = city.id"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt1->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt1->bind_result($id, $name, $city, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt1->fetch()){
    echo '<option value=" '. $id . ' "> ' . $name . ", " . $city . " " . $state . '</option>\n';
}
$stmt1->close();
?>
        </select>
        <p><button type="submit">delete</button></p>
      </fieldset>
    </form>
  </div>

  <div>
    <form method="post" action="add-hosc.php"> 
      <fieldset>
        <legend>Add House-School Relationship</legend>
        <p>Remember to check if the relationship already exists before attempting to add a new one. There's a table below here to check.</p>
        <label>House</label>
        <select name="house_id">
<?php
if(!($stmt = $mysqli->prepare("SELECT house.id, street_number, street_name, zip_code, name, state FROM house LEFT JOIN city ON house.city_id = city.id"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $number, $name, $zip, $city_name, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
    echo '<option value=" '. $id . ' "> ' . $number . " " . $name . ", " . $city_name . " " . $state . " " . $zip . '</option>\n';
}
?>
        </select>
        <br>                     
        <label>School</label>
        <select name="school_id">
<?php
if(!($stmt1 = $mysqli->prepare("SELECT school.id, school.name, city.name, state FROM school LEFT JOIN city ON school.city_id = city.id"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt1->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt1->bind_result($id, $name, $city, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt1->fetch()){
    echo '<option value=" '. $id . ' "> ' . $name . ", " . $city . " " . $state . '</option>\n';
}
$stmt1->close();
?>
        </select>
        <p><input type="submit" /></p>
      </fieldset>
    </form>
  </div>

  <div>
    <form method="post" action="delete-hosc.php"> 
      <fieldset>
        <legend>Delete House-School Relationship</legend>
        <p>Remember to check if the relationship even exists before attempting to delete it. There's a table below here to check.</p>
        <label>House</label>
        <select name="house_id">
<?php
if(!($stmt = $mysqli->prepare("SELECT house.id, street_number, street_name, zip_code, name, state FROM house LEFT JOIN city ON house.city_id = city.id"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $number, $name, $zip, $city_name, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
    echo '<option value=" '. $id . ' "> ' . $number . " " . $name . ", " . $city_name . " " . $state . " " . $zip . '</option>\n';
}
?>
        </select>
        <br>                     
        <label>School</label>
        <select name="school_id">
<?php
if(!($stmt1 = $mysqli->prepare("SELECT school.id, school.name, city.name, state FROM school LEFT JOIN city ON school.city_id = city.id"))){
    echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt1->execute()){
    echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt1->bind_result($id, $name, $city, $state)){
    echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt1->fetch()){
    echo '<option value=" '. $id . ' "> ' . $name . ", " . $city . " " . $state . '</option>\n';
}
$stmt1->close();
?>
        </select>
        <p><input type="submit" /></p>
      </fieldset>
    </form>
  </div>

</fieldset>
</div>

<div>
  <h3>House-School Listing</h3>
  <p>This is mostly to make adding and removing relationships easier.</p>
  <table>
  <thead>
    <tr>
      <th>Address</th>
      <th>City</th>
      <th>ZIP</th>
      <th>School</th>
      <th>Type</th>
    </tr>
    </thead>
    <tbody>
<?php
if(!($stmt = $mysqli->prepare("SELECT street_number, street_name, city.name, state, zip_code, school.name, school.type FROM house INNER JOIN house_school ON house.id = house_school.house_id INNER JOIN school ON house_school.school_id = school.id LEFT JOIN city ON house.city_id = city.id"))){
  echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
  echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($street_num, $street_name, $city_name, $state, $zip, $school, $type)){
  echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>" . $street_num . " " . $street_name . "</td>\n<td>" . $city_name . " " . $state . "</td>\n<td>" . $zip . "</td>\n<td>" . $school . "</td>\n<td>" . $type . "</td>\n</tr>";
}
$stmt->close();
?>
  </tbody>
  </table>
</div>

</body>
</html>