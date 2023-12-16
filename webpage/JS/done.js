document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#button-press');
    if(form){
    form.addEventListener('press', check, true);}
});

//Get the prompt input


async function wcheck(event){
    var prompt = document.getElementById("loads");

    var lprompt = document.getElementById("loadq");

    var btnt = document.getElementById("btnload");

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
    event.preventDefault();
}
