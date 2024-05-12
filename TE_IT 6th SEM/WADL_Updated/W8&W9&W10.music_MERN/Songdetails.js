const mongoose = require("mongoose")

const SongdetailsSchema = new mongoose.Schema({
    Songname: String,
    Film: String,
    Music_director: String,
    singer: String,
    Actor: String,
    Actress: String
})

// creating Model of defined schema `SongdetailsSchema` and then exporting
const Songdetails = mongoose.model("songdetails", SongdetailsSchema);
module.exports = Songdetails;