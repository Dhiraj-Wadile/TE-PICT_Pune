const mongoose = require("mongoose");

const StudentSchema = new mongoose.Schema({
  name: String,
  dbMarks: String, // Assuming film is an integer
  rollNumber: Number, // Assuming roll number is an integer
  ccMarks: String, // Assuming cc stands for credit points or marks
  cnsMarks: String, // Assuming cns stands for course name
  paMarks: String, // Assuming pa stands for performance assessment
});

// creating Model of defined schema `StudentSchema` and then exporting
const Student = mongoose.model("Student", StudentSchema);
module.exports = Student;
