// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#uploadForm');
    const userForm = document.querySelector('#userLogin');
    const loginForm = document.querySelector('#button-press');

    //  For load/upload options
    if(form){
        form.addEventListener('submit', uploadFileForBalance, true);
        form.addEventListener('submit', uploadFileForLoad, true);
    }
    if(userForm){userForm.addEventListener('submit', userLogin, true);} //  For when user submits a new login
    if(loginForm){loginForm.addEventListener('press', showLoginForm, true);}  //  For showing login pane
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
        alert(error + "\nPlease contact Administrator");   //  Add alert if unsuccessful
    }

    // Stops page from reloading to submit the form
    event.preventDefault();
}

/**
 * @function uploadFileForBalance
 * This function handles a file submission from a webpage with a form
 * It looks for a form element in the document, and processes the file info
 * @param {Event} event handles
 * @returns {Promise<void>}
 */
async function uploadFileForBalance(event) {
    const form = event.currentTarget;
    const fileInput = document.getElementById("bala");
    const ids = document.createElement('id');
    const file = fileInput.files[0];    //  Get teh file
    localStorage.setItem("fileName", file.name);   //  And store the name
    const id = fileInput.form.id;
    var loadingLabel = document.getElementById("title_label");

    const formData = new FormData();
    formData.append('bala', file);
    formData.append('id', id);
    
    if (file) {
        const reader = new FileReader();
    
        reader.onload = function (e) {
          const content = e.target.result;
          localStorage.setItem("grids", content)
        };
    
        reader.readAsText(file);
    }

    try {
        loadingLabel.textContent = `Solving Balance Task for (${localStorage.getItem("fileName")})...`
        const response = await fetch('/balanced', {
            method: 'POST',
            body: formData
        });

        loadingLabel.textContent = "Balance Task Done!";
        loadingLabel.style.color = "green";

        const data = await response.json();
        console.log('Success:', data);
        console.log('ID Upload: ', id);

        //  Store data here
        localStorage.setItem("solution", JSON.stringify(data));
    } catch (error) {
        console.error('Error:', error);
    }

    window.location = "/balance.html";

    // Stops page from reloading to submit the form
    event.preventDefault();
}

/**
 * @function uploadFileForLoad
 * This function handles a file submission from a webpage with a form
 * It looks for a form element in the document, and processes the file info
 * @param {Event} event handles
 * @returns {Promise<void>}
 */
async function uploadFileForLoad(event) {
    const form = event.currentTarget;
    const fileInput = document.getElementById("offload");
    const ids = document.createElement('id');
    const file = fileInput.files[0];    //  Get teh file
    const id = fileInput.form.id;
    var loadingLabel = document.getElementById("title_label");

    const formData = new FormData();
    formData.append('offload', file);
    formData.append('id', id);

    if (file) {
        const reader = new FileReader();
    
        reader.onload = function (e) {
          const content = e.target.result;
          localStorage.setItem("grids", content)
        };
    
        reader.readAsText(file);
    }
    
    try {
        loadingLabel.textContent = `Solving Load Task for (${localStorage.getItem("fileName")})...`
        const response = await fetch('/load', {
            method: 'POST',
            body: formData
        });

        loadingLabel.textContent = "Load Task Done!";
        loadingLabel.style.color = "green";

        const data = await response;
        console.log('Success:', data);
        console.log('ID Upload: ', id);
    } catch (error) {
        console.error('Error:', error);
    }
    window.location.replace("http://localhost:8080/load.html");

    // Stops page from reloading to submit the form
    event.preventDefault();
}
/**
 * @function showLoginForm
 * Shows the modal menu on the login form
 * @param {Event} event 
 */
async function showLoginForm(event){
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
 * @function backToIntro
 * Relocates user back to the intro webpage
 * @param NONE
 */
async function backToIntro(event){
    // const response = await fetch('/start', {
    //     method: 'POST'
    // });

    // var status = await response.status;

    // if(status === 200){
    //     window.location = "/intro.html"
    // }
    window.location = "/intro.html"
}

//  Init modals here
//  This is to avoid having to press buttons twice for modals
window.onload = async function(){
    await showLoginForm();
    localStorage.clear();
    await fetch('/clear/load', {
        method: 'GET',
    });
};
