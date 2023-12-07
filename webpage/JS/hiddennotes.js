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
    event.preventDefault();
}
