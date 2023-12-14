document.addEventListener('DOMContentLoaded', (event) => {
    const loginForm = document.querySelector('#button-press');
    if(loginForm){
    loginForm.addEventListener('press', showLoginForm, true);}
});

//Get the prompt input


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
    event.preventDefault();
}
