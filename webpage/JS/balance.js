// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
    const notesForm = document.querySelector('#userNotes');
    const notesConfirm = document.querySelector('#button-press');

    //  For the user notes button
    if(notesForm){notesForm.addEventListener('submit', userNotes, true);}

    //  And the notes confirm button
    if(notesConfirm){notesConfirm.addEventListener('press', notecheck, true);}
});
/**
 * @function showLoginForm
 * Shows the modal menu on the login form
 * @param {Event} event 
 */
async function showLoginForm(){
    var prompt2 = document.getElementById("login");

    var btn = document.getElementById("btnlog");

    var btnn = document.getElementById("ssm");

    var span = document.getElementsByClassName("close2")[0];

    btn.onclick = function(){
        prompt2.style.display = "block";
    }

    span.onclick = function(){
        prompt2.style.display = "none";
    }

    btnn.onclick = function(){
        prompt2.style.display = "none";
    }

    window.onclick = function(event){
        if(event.target == prompt2){
            prompt2.style.display = "none";
        }}

    if(event){
        event.preventDefault();
    }
}

/**
 * @function userLogin
 * This file will handle the user login inputs from all employees
 * 
 * @param {Event} event handles the event settings
 * @returns {Promise<void>}
 */
async function userLogin(event) {
    const form = event.currentTarget;
    const login = document.getElementById("name").value;
    document.getElementById("name").value = '';
    // const ids = document.createElement('id');
    // const logins = login.value;    //  Get teh file
    // const id = login.form.id;

    const formData = new FormData();
    formData.append('name', login);
    // formData.append('id', id);

    try {
        const response = await fetch('/id', {
            method: 'POST',
            body: formData
        });

        const data = await response;
        console.log('Success:', data);
        console.log('User: ', login);
    } catch (error) {
        console.error('Error:', error);
        alert(error + "\nPlease contact Administrator");   //  Add alert if unsuccessful
    }

    // Stops page from reloading to submit the form
    event.preventDefault();
}

/**
 * @function userNotes
 * Displays a modal menu allowing the user to input a note to the log
 * @param {Event} event handles the event settings
 * @returns {Promise<void>}
 */
async function userNotes() {
    const note = document.getElementById("nnote").value;
    document.getElementById("nnote").value = '';
    // const ids = document.createElement('id');
    // const logins = login.value;    //  Get teh file
    // const id = login.form.id;

    const formData = new FormData();
    formData.append('nnote', note);
    // formData.append('id', id);

    try {
        const response = await fetch('/notes', {
            method: 'POST',
            body: formData
        });

        const data = await response;
        console.log('Success:', data);
        console.log('Custom Notes: ', note);
    } catch (error) {
        console.error('Error:', error);
    }

    // Stops page from reloading to submit the form
    event.preventDefault();
}

/**
 * @function noteCheck
 * Checks for the users valid note, upload if valid
 */
async function notecheck(){
    var prompt = document.getElementById("notes");

    var btnz = document.getElementById("btnotes");

    var btnnz = document.getElementById("snm");


    var span = document.getElementsByClassName("close")[0];

    btnz.onclick = function(){
        prompt.style.display = "block";
    }

    span.onclick = function(){
        prompt.style.display = "none";
        // document.getElementById("name").value = '';
    }

    btnnz.onclick = function(){
        prompt.style.display = "none";
    }

    window.onclick = function(event){
        if(event.target == prompt){
            prompt.style.display = "none";
        }}
    event.preventDefault();
}

async function processContent(content) {

    //  Reset move count
    moveNum = 1;

    const lines = content.split('\n');

    //  Get the buffer item
    var bay = document.getElementById("bay_grid");
    var buffer = document.getElementById("buffer_grid");
    var movesContainer = document.getElementById("movesContainer");
    var bayContent = "";
    var bufferContent = "";
    var solutionContent = JSON.parse(localStorage.getItem("solution"));
    // var resetPress = document.getElementById("prevmove_btn");
    // var fel = document.getElementById("balfin");

    // resetPress.onclick = function(){
    //     fel.style.display = "block";
    // }

    var solutionState = solutionContent["endState"];
    delete solutionContent["endState"];


    console.log(solutionState);
  
    //  Populate the bay
    for (const line of lines) {
      const match = line.match(/\[(\d+),(\d+)\], \{(\d+)\}, (\w+)/);
  
      if (match) {
        const [, yPosition, xPosition, mass, name] = match;

        // Remove leading zeros from x and y positions
        const cleanedYPosition = parseInt(yPosition, 10).toString();
        const cleanedXPosition = parseInt(xPosition, 10).toString();

        if(name === "UNUSED"){
            bayContent += `<div class="grid-item grid-unused" id="(${cleanedYPosition},${cleanedXPosition})"><div class="grid-item-content"></div></div>`;
        }else if(name === "NAN"){
            bayContent += `<div class="grid-item grid-nan" id="(${cleanedYPosition},${cleanedXPosition})"><div class="grid-item-content">${name[0]}</div></div>`;
        }else{
            bayContent += `<div class="grid-item grid-container" id="(${cleanedYPosition},${cleanedXPosition})" onclick="highlightContainer('(${cleanedYPosition},${cleanedXPosition})')"><div class="grid-item-content">${name}</div></div>`;
        }
      }
    }

    //  And the buffer
    for(let x = 0; x < 96; x++){
      bufferContent += `<div class="grid-item grid-unused" id="UNUSED"><div class="grid-item-content">U</div></div>`;
    }

    // console.log(content);
    bay.innerHTML = bayContent;
    buffer.innerHTML = bufferContent;

    //  Highlight first move
    await highlightNextMove();
}

async function displayMoves(){

    

    //  Get needed html elements
    var movesContainer = document.getElementById("movesContainer");
    
    //  Get all the moves
    var moves = JSON.parse(localStorage.getItem("solution"));
    delete moves['startState'];
    delete moves['endState'];

    var totalCost = 0;

    var allMoves = ``;

    for(let i = 1; i <= Object.keys(moves).length; i++){

        const moveData = moves[i.toString()];
        allMoves += `<div class="container" id="container${i}">
            <div class="header" id="header${i}">${moveData.containerName}</div>
            <div id="mass${i}">Mass: ${moveData.mass}</div>
            <div class="pickup-putdown" id="pickup${i}">FROM ${moveData.pickup_origin}: (${moveData.pickup_x}, ${moveData.pickup_y})</div>
            <div class="pickup-putdown" id="putdown${i}">TO ${moveData.putdown_origin}: (${moveData.putdown_x}, ${moveData.putdown_y})</div>
            <div class="cost" id="cost${i}">${moveData.cost} min</div>
            </div>`
        
        totalCost += parseInt(moveData.cost);
    }

    movesContainer.innerHTML = allMoves;
    document.getElementById("bayHeader").textContent = "Estimated Time: " + totalCost + " minutes";
}

async function highlightNextMove(){

    //  Get JSON data
    var moveData = JSON.parse(localStorage.getItem("solution"))[`${moveNum}`];
    var findone = document.getElementById("balfin");
    //  Reset all move colors
    var containers = document.getElementsByClassName("container");
    var containerArray = Array.from(containers);
    containerArray.forEach(function(container, index) {
        container.style.backgroundColor = "#ccc";
    });

    //  Remove special coloring of last move
    var allGridItems = Array.from(document.getElementsByClassName("grid-item"));
    allGridItems.forEach(function(item, index){
        if(item.classList.contains("grid-pickup")){item.classList.remove("grid-pickup");}
        if(item.classList.contains("grid-putdown")){item.classList.remove("grid-putdown");}
    });

    //  Highlight the move
    var move = document.getElementById(`container${moveNum}`);
    if(move == null){
        findone.style.display = "block";
     }
    move.style.backgroundColor = "yellow";

    //  Highlight specified containers by adding class to grid items
    var pickupContainer = document.getElementById(`(${moveData.pickup_y},${moveData.pickup_x})`)
    var putdownSlot = document.getElementById(`(${moveData.putdown_y},${moveData.putdown_x})`)

    //  Also get the names
    var pickupName = pickupContainer.innerHTML;
    var putdownName = putdownSlot.innerHTML;

    //  Swap the names
    pickupContainer.innerHTML = putdownName;
    putdownSlot.innerHTML = pickupName;

    pickupContainer.classList.add("grid-pickup");
    pickupContainer.classList.add("grid-unused");
    pickupContainer.classList.remove("grid-container")

    putdownSlot.classList.add("grid-putdown");
    putdownSlot.classList.add("grid-container");
    putdownSlot.classList.remove("grid-unused")

    moveNum++;

}

async function backToUpload(){
    const result = window.confirm("Your current task data will be lost. Are you sure?");
    if(result){
        localStorage.clear();
        window.location = '/fileupload.html';
    }
}

async function finishTask(){
    const result = window.confirm("Your current task data will be lost. Are you sure you are completed?");
    if(result){
        window.location = '/noticeblock.html';
    }
}

window.onload = async function(){
    await displayMoves();
}