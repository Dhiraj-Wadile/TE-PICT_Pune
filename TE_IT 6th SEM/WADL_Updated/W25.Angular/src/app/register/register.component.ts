import { Component } from '@angular/core';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent {
  username: string = '';
  password: string = '';
  email: string = '';
  phone: string = '';
  course: string = ''; // Declare the course property

  registerUser() {
    const userData = { username: this.username, password: this.password, email: this.email, phone: this.phone, course: this.course }; // Include course in user data
    localStorage.setItem('userData', JSON.stringify(userData));
    console.log('Data stored in localStorage:', this.username); // Log the data
    alert('Registration successful!');
  }
}
