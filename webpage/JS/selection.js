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

    btn.onclick = function(){
        prompt.style.display = "block";
    }

    span.onclick = function(){
        prompt.style.display = "none";
        document.getElementById("name").value = '';
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
