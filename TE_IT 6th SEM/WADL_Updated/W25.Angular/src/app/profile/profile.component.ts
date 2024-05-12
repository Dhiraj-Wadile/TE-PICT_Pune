import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-profile',
  templateUrl: './profile.component.html',
  styleUrls: ['./profile.component.css']
})
export class ProfileComponent implements OnInit {
  userData: any;

  constructor(private router: Router) {}

  ngOnInit() {
    const currentUserString = sessionStorage.getItem('currentUser');
    if (currentUserString) {
      this.userData = JSON.parse(currentUserString);
    } else {
      // If no user is logged in, navigate back to the login page
      this.router.navigate(['/login']);
    }
  }
}
