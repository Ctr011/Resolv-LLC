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
    var prompt = document.getElementById("login");

    var btn = document.getElementById("btnlog");

    var btnn = document.getElementById("ssm");

    var span = document.getElementsByClassName("close")[0];

    btn.onclick = function(){
        prompt.style.display = "block";
    }

    span.onclick = function(){
        prompt.style.display = "none";
    }

    btnn.onclick = function(){
        prompt.style.display = "none";
    }

    window.onclick = function(event){
        if(event.target == prompt){
            prompt.style.display = "none";
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
    const lines = content.split('\n');

    //  Get the buffer item
    var bay = document.getElementById("bay_grid");
    var buffer = document.getElementById("buffer_grid");
    var movesContainer = document.getElementById("movesContainer");
    var bayContent = "";
    var bufferContent = "";
    var solutionContent = JSON.parse(localStorage.getItem("solution"));

    var solutionState = solutionContent["endState"];
    delete solutionContent["endState"];


    console.log(solutionState);
  
    //  Populate the bay
    for (const line of lines) {
      const match = line.match(/\[(\d+),(\d+)\], \{(\d+)\}, (\w+)/);
  
      if (match) {
        const [, yPosition, xPosition, mass, name] = match;

        if(name === "UNUSED"){
            bayContent += `<div class="grid-item grid-unused" id="${name}@(${yPosition},${xPosition})"><div class="grid-item-content">${name[0]}</div></div>`;
        }else if(name === "NAN"){
            bayContent += `<div class="grid-item grid-nan" id="${name}"><div class="grid-item-content">${name[0]}</div></div>`;
        }else{
            bayContent += `<div class="grid-item grid-container" id="${name}"><div class="grid-item-content">${name[0]}</div></div>`;
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
  }