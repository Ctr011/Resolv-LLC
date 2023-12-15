//passing in data
var contmass;
var contname;
async function processContent(content) {
    const lines = content.split('\n');
    //  Get the buffer item
    var bay = document.getElementById("bay_grid");
    var buffer = document.getElementById("buffer_grid");
    var bayContent = "";
    var bufferContent = "";

    moveNum = 1;

    var bayContent = "";
  
    for (const line of lines) {
      const match = line.match(/\[(\d+),(\d+)\], \{(\d+)\}, (\w+)/);
  
      if (match) {
        const [, yPosition, xPosition, mass, name] = match;
        const cleanedYPosition = parseInt(yPosition,10).toString();
        const cleanedXPosition = parseInt(xPosition,10).toString();
        const cleanedMass = parseInt(mass,10).toString();

        if(name === "UNUSED"){
            bayContent += `<div class="grid-item grid-unused" id="${name}"><div class="grid-item-content"></div></div>`;
        }else if(name === "NAN"){
            bayContent += `<div class="grid-item grid-nan" id="${name}"><div class="grid-item-content"></div></div>`;
        }else{
            bayContent += `<div class="grid-item grid-container" data-mass="${cleanedMass}" data-name="${name}" data-same="false" id="${cleanedYPosition},${cleanedXPosition}" onclick="unloadcheck((${cleanedYPosition}+','+ ${cleanedXPosition}))"><div class="grid-item-content">${name}</div></div>`;
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

async function highlightNextMove(){

    //  Get JSON data
    var moveData = JSON.parse(localStorage.getItem("solution"))[`${moveNum}`];

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


async function displayMoves(){
  //  Get needed html elements
  var movesContainer = document.getElementById("movesContainer");
  
  //  Get all the moves
  var moves = JSON.parse(localStorage.getItem("solution"));
  delete moves['startState'];
  delete moves['endState'];

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
  }

  movesContainer.innerHTML = allMoves;

}


  async function tester(id){
    if(document.getElementById(id).style.backgroundColor == "blue"){
      document.getElementById(id).style.backgroundColor = "orange";
    }
    else{
      document.getElementById(id).style.backgroundColor = "blue";
    }
    // alert("Passing ID: " + id);
  }

// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#userNotes');
    if(form){
    form.addEventListener('submit', loadcheck, true);}
});


/**
 * @function loadcheck
 * This file will handle the user login inputs from all employees
 * 
 * @param {Event} event handles the event settings
 * @returns {Promise<void>}
 */

async function loadcheck(event) {
    const form = event.currentTarget;
    const contn = document.getElementById("contn").value;
    const contw = document.getElementById('contw').value;
    document.getElementById("contn").value = '';
    document.getElementById("contw").value = '';

    //  Get the loads container
    let loadContainer = document.getElementById("loadsContainer");
    let addButton = document.getElementById("newContainerBtn");
    let loadContainerData = "";
    
    //  Delete add button if visible
    if(addButton){addButton.remove()}

    loadContainerData += `
        <div class="load-containers" id="load${contn}">
          <div class="header">${contn}</div>
          <div class="mass">Mass: ${contw}</div>
        </div>`
    
        loadContainer.innerHTML += loadContainerData

    const formData = new FormData();
    formData.append('contn', contn);
    formData.append('contw', contw);

    try {
        const response = await fetch('/contname', {
            method: 'POST',
            body: formData
        });

        const data = await response;
        console.log('Success:', data);
        console.log('Container Name: ', contn);
        console.log('Container Weight: ', contw);
    } catch (error) {
        console.error('Error:', error);
    }

    // Stops page from reloading to submit the form
    event.preventDefault();
}

document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#userNotes');
    if(form){
    form.addEventListener('submit', unloadcheck, true);}
});
/**
 * @function unloadcheck
 * This file will handle the user login inputs from all employees
 * 
 * @param {Event} event handles the event settings
 * @returns {Promise<void>}
 */
async function unloadcheck(id){
    const form = id.currentTarget;
    const contn = document.getElementById(id).getAttribute('data-name');  //  Container name
    const contw = document.getElementById(id).getAttribute('data-mass');  //  container mass
    var delete_data = "No";
    var s = document.getElementById(id).getAttribute('data-same');

    var unloads = document.getElementById('unloadsContainer');  //  Reference the unloads container
    var unloadsContainer = "";  //  Holds the raw HTML text to go inside unloads container

    //  ID-ing by colour? sure
    if(document.getElementById(id).style.backgroundColor === "orange"){
        delete_data = "Yes";

        //  Get element, and remove
        let containerToBeRemoved = document.getElementById(`unload${contn}`);
        if(containerToBeRemoved){containerToBeRemoved.remove()}

        //  Reset color
        document.getElementById(id).style.backgroundColor = "blue"

    }
    else{
        document.getElementById(id).style.backgroundColor = "orange";
        delete_data = "No";

        //  Create the display for the picked up Container here
        unloadsContainer += `
        <div class="unload_containers" id="unload${contn}">
          <div class="header">${contn}</div>
          <div class="mass">Mass: ${contw}</div>
        </div>`
        unloads.innerHTML += unloadsContainer;
    }

    



    const formData = new FormData();
    formData.append('contn', contn);
    formData.append('contw', contw);
    formData.append('delete_data', delete_data);
    // formData.append('id', id);

    try {
        const response = await fetch('/contless', {
            method: 'POST',
            body: formData
        });

        const data = await response;
        console.log('Success:', data);
        console.log('Container Name: ', contn);
        console.log('Container Weight: ', contw);
        console.log('delete_data', delete_data);
    } catch (error) {
        console.error('Error:', error);
    }

    // Stops page from reloading to submit the form

}


document.addEventListener('DOMContentLoaded', (event) => {
  const form = document.querySelector('#button-press');
  if(form){
  form.addEventListener('press', wcheck, true);}
});

//Get the prompt input

//LoadPromptFile
async function wcheck(event){
  var prompt = document.getElementById("loads");

  var lprompt = document.getElementById("loadq");

  var btnt = document.getElementById("newContainerBtn");

  var btnx = document.getElementById("snn");

  var ybtn = document.getElementById("yload");
  var nbtn = document.getElementById("nload");

  


  var span3 = document.getElementsByClassName("close3")[0];

  btnt.onclick = function(){
      prompt.style.display = "block";
  }

  span3.onclick = function(){
      prompt.style.display = "none";
      lprompt.style.display = "none";
  }

  btnx.onclick = function(){
      prompt.style.display = "block";
      lprompt.style.display = "block";
  }
  ybtn.onclick = function(){
      prompt.style.display = "block";
      lprompt.style.display = "none";
  }
  nbtn.onclick = function(){
      prompt.style.display = "none";
      lprompt.style.display = "none";
  }

  window.onclick = function(event){
      if(event.target == prompt){
          prompt.style.display = "none";
      }}
}

//HiddenNotes
document.addEventListener('DOMContentLoaded', (event) => {
  const form = document.querySelector('#button-press');
  if(form){
  form.addEventListener('press', notecheck, true);}
});

//Get the prompt input


async function notecheck(event){
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
}

document.addEventListener('DOMContentLoaded', (event) => {
  const form = document.querySelector('#button-press');
  if(form){
  form.addEventListener('press', check, true);}
});

//Get the prompt input


async function check(event){
  var prompt = document.getElementById("login");

  var btn = document.getElementById("btnlog");

  var btnn = document.getElementById("ssm");


  var span = document.getElementsByClassName("close")[0];
  var span2 = document.getElementsByClassName("close2")[0];

  btn.onclick = function(){
      prompt.style.display = "block";
  }

  span.onclick = function(){
      prompt.style.display = "none";
  }
  span2.onclick = function(){
      prompt.style.display = "none";
  }
  btnn.onclick = function(){
      prompt.style.display = "none";
  }

  window.onclick = function(event){
      if(event.target == prompt){
          prompt.style.display = "none";
      }}
  event.preventDefault();
}

//userlogin
// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
  const form = document.querySelector('#userLogin');
  if(form){
  form.addEventListener('submit', userLogin, true);}
});


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
  }

  // Stops page from reloading to submit the form
  event.preventDefault();
}

//CustomLogs
// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
  const form = document.querySelector('#userNotes');
  if(form){
  form.addEventListener('submit', userNotes, true);}
});


/**
* @function userNotes
* This file will handle the user login inputs from all employees
* 
* @param {Event} event handles the event settings
* @returns {Promise<void>}
*/

async function userNotes(event) {
  const form = event.currentTarget;
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

async function userStart(event){
  const form = event.currentTarget;
  const speak = document.getElementById("sbtn");
  const formData = new FormData();
  formData.append("info", localStorage.getItem("grids"));
  formData.append("start", "start");
  try {
    const response = await fetch('/start', {
        method: 'POST',
        body: formData
    });

    const data = await response;
    console.log('Success:', data);
  } catch (error) {
    console.error('Error:', error);
    alert(error + "\nPlease contact Administrator");   //  Add alert if unsuccessful
}
  event.preventDefault();
}

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

async function backToUpload(){
  const result = window.confirm("Your current task data will be lost. Are you sure?");
  if(result){
      localStorage.clear();
      window.location = '/fileupload.html';
  }
}

window.onload = async function(){
  await processContent(localStorage.getItem("grids"))

  //  call here so we don;t have to click twice
  showLoginForm()
  notecheck();
  wcheck();
}

