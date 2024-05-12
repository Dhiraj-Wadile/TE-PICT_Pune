/* ****************Importing Required Modules/Packages***************** */
const express = require("express");
const mongoose = require("mongoose");
const Songdetails = require("./Student");
const app = express();

/* ******************Configuring Middleware(s)***************** */
app.use(express.json());

// /* ******************Defining Configuration Variables***************** */
// const db_connection = "mongodb://127.0.0.1:27017/Music123";
// const port = 2324;

/* ******************Defining Configuration Variables***************** */
const db_connection = "mongodb+srv://Dhiraj123:Dhiraj123@cluster0.e6ykgub.mongodb.net/";
const port = 2324;








app.use(express.static("public"));

/* *********************Defining Routes and Controllers********************* */

// Add a new student
app.post("/addStudent", async function (request, response) {
  // Get data from body
  const { name, rollNumber, cnsMarks, dbMarks, ccMarks, paMarks } =
    request.body;
  const student = await Songdetails.create({
    name,
    rollNumber,
    cnsMarks,
    dbMarks,
    ccMarks,
    paMarks,
  });
  response.send({ message: "Student added successfully", student });
});

// Display total count of students and list all students
app.get("/displayStudents", async function (request, response) {
  const students = await Songdetails.find();
  response.send({ "total count": students.length, students });
});

// Delete a student
app.delete("/delete/:studentRollNumber", async function (request, response) {
  const studentRollNumber = request.params.studentRollNumber;
  const result = await Songdetails.deleteOne({ rollNumber: studentRollNumber });
  response.send({ message: "Student deleted successfully", result });
});

// List students by CNS marks
app.get(
  "/getStudentsByCNSMarks/:cnsMarksFilter",
  async function (request, response) {
    const cnsMarksFilter = request.params.cnsMarksFilter;
    const students = await Songdetails.find({
      cnsMarks: { $gte: cnsMarksFilter },
    });
    response.send(students);
  }
);

// List students by DB marks
app.get(
  "/getStudentsByDBMarks/:dbMarksFilter",
  async function (request, response) {
    const dbMarksFilter = request.params.dbMarksFilter;
    const students = await Songdetails.find({
      dbMarks: { $gte: dbMarksFilter },
    });
    response.send(students);
  }
);

// Display all students in a table
app.get("/displayAllStudentsInTable", async function (request, response) {
  const students = await Songdetails.find();

  // Creating table view for browser
  let html = "<table border=1 style='border-collapse: collapse'>";
  html +=
    "<tr><th>Name</th><th>Roll Number</th><th>CNS Marks</th><th>DB Marks</th><th>CC Marks</th><th>PA Marks</th></tr>";
  students.forEach((student) => {
    html += `<tr><td>${student.name}</td><td>${student.rollNumber}</td><td>${student.cnsMarks}</td><td>${student.dbMarks}</td><td>${student.ccMarks}</td><td>${student.paMarks}</td></tr>`;
  });
  html += "</table>";
  response.send(html);
});
// Update all marks for a student by roll number
app.put("/updateMarks/:rollNumber", async function (request, response) {
  try {
    const rollNumber = request.params.rollNumber;
    // Find the student by roll number
    const student = await Songdetails.findOne({ rollNumber });
    if (!student) {
      return response.status(404).send({ message: "Student not found" });
    }
    // Update all marks by adding 10 to each mark
    student.cnsMarks = (parseInt(student.cnsMarks) + 10).toString();
    student.dbMarks = (parseInt(student.dbMarks) + 10).toString();
    student.ccMarks = (parseInt(student.ccMarks) + 10).toString();
    student.paMarks = (parseInt(student.paMarks) + 10).toString();
    // Save the updated student object
    await student.save();
    response.send({ message: "Marks updated successfully", student });
  } catch (error) {
    console.error("Error updating marks:", error);
    response.status(500).send({ message: "Error updating marks" });
  }
});
// List names of students who got more than 25 marks in all subjects
app.get("/studentsAbove25Marks", async function (request, response) {
  try {
    const students = await Songdetails.find({
      cnsMarks: { $gte: 25 },
      dbMarks: { $gte: 25 },
      ccMarks: { $gte: 25 },
      paMarks: { $gte: 25 }
    }).select('name');

    const names = students.map(student => student.name);
    response.send(names);
  } catch (error) {
    console.error("Error fetching students:", error);
    response.status(500).send({ message: "Error fetching students" });
  }
});




/* ***********Database Connection And Starting Express Server********** */
console.log(
  "Waiting for the database to connect. After connection, the server will start..."
);
mongoose
  .connect(db_connection)
  .then(() => {
    app.listen(port, function () {
      console.log(">>>> Database connected successfully and server is started");
      console.log("http://localhost:" + port);
    });
  })
  .catch((error) => {
    console.log("Problem connecting to the database");
    console.log(error);
  });
