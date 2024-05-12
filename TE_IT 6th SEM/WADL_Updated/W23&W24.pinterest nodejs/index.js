const express = require("express");
const path = require("path");

const app = express();

const cardData = [
  { date: "2024-05-01", description: "Card 1 content from backend" },
  { date: "2024-04-30", description: "Card 2 content from backend" },
  { date: "2024-04-29", description: "Card 3 content from backend" },
  { date: "2024-04-28", description: "Card 4 content from backend" },
  { date: "2024-05-01", description: "Card 1 content from backend" },
  { date: "2024-04-30", description: "Card 2 content from backend" },
  { date: "2024-04-29", description: "Card 3 content from backend" },
  { date: "2024-04-28", description: "Card 4 content from backend" },
  { date: "2024-05-01", description: "Card 1 content from backend" },
  { date: "2024-04-30", description: "Card 2 content from backend" },
  { date: "2024-04-29", description: "Card 3 content from backend" },
  { date: "2024-04-28", description: "Card 4 content from backend" },
  { date: "2024-05-01", description: "Card 1 content from backend" },
  { date: "2024-04-30", description: "Card 2 content from backend" },
  { date: "2024-04-29", description: "Card 3 content from backend" },
  { date: "2024-04-28", description: "Card 4 content from backend" },
  { date: "2024-05-01", description: "Card 1 content from backend" },
  { date: "2024-04-30", description: "Card 2 content from backend" },
  { date: "2024-04-29", description: "Card 3 content from backend" },
  { date: "2024-04-28", description: "Card 4 content from backend" },
  { date: "2024-05-01", description: "Card 1 content from backend" },
  { date: "2024-04-30", description: "Card 2 content from backend" },
  { date: "2024-04-29", description: "Card 3 content from backend" },
  { date: "2024-04-28", description: "Card 4 content from backend" },
  { date: "2024-05-01", description: "Card 1 content from backend" },
  { date: "2024-04-30", description: "Card 2 content from backend" },
  { date: "2024-04-29", description: "Card 3 content from backend" },
  { date: "2024-04-28", description: "Card 4 content from backend" },
  { date: "2024-05-01", description: "Card 1 content from backend" },
  { date: "2024-04-30", description: "Card 2 content from backend" },
  { date: "2024-04-29", description: "Card 3 content from backend" },
  { date: "2024-04-28", description: "Card 4 content from backend" },
  { date: "2024-05-01", description: "Card 1 content from backend" },
  { date: "2024-04-30", description: "Card 2 content from backend" },
  { date: "2024-04-29", description: "Card 3 content from backend" },
  { date: "2024-04-28", description: "Card 4 content from backend" }
];

app.get("/", (req, res) => {
  res.sendFile(path.join(__dirname, "index.html"));
});

// Endpoint to send card data
app.get("/cards", (req, res) => {
  res.json(cardData);
});

app.listen(3000, () => {
  console.log("app running");
});
