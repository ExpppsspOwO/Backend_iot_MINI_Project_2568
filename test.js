// const mysql = require("mysql2");

// const db = mysql.createConnection({
//   host: "127.0.0.1",
//   user: "root",
//   password: "sword_code_is_3",
// });

db.connect((err) => {
  if (err) throw err;
  console.log("✅ Connected to MySQL in Docker!");
});