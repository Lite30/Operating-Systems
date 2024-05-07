<?php
// Database connection parameters
$servername = "localhost";
$username = "root";
$password = ""; // You had a space here, it should be empty if there's no password
$dbname = "db_NEMsyss";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Fetch data from the form
$studentNumber = $_POST['studentNumber'];
$programCode = $_POST['programCode'];
$firstName = $_POST['firstName'];
$lastName = $_POST['lastName'];

// SQL to insert data into the table
$sql = "INSERT INTO students (student_number, program_code, first_name, last_name)
VALUES ('$studentNumber', '$programCode', '$firstName', '$lastName')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
