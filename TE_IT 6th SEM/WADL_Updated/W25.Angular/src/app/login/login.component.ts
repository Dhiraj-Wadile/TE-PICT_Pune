// login.component.ts
import { Component } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {
  username: string = '';
  password: string = '';

  constructor(private router: Router) {}

  login() {
    const userDataString = localStorage.getItem('userData');
    if (userDataString) {
      const userData = JSON.parse(userDataString);
      if (userData.username === this.username && userData.password === this.password) {
        sessionStorage.setItem('currentUser', JSON.stringify(userData));
        this.router.navigate(['/profile'], { state: { userData } });
      } else {
        alert('Invalid username or password');
      }
    } else {
      alert('User not registered');
    }
  }
}
