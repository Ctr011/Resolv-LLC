

function processContent(content) {
    const lines = content.split('\n');

    //  Get the buffer item
    var bay = document.getElementById("bay_grid");
    var bayContent = "";
  
    for (const line of lines) {
      const match = line.match(/\[(\d+),(\d+)\], \{(\d+)\}, (\w+)/);
  
      if (match) {
        const [, yPosition, xPosition, mass, name] = match;
        const cleanedYPosition = parseInt(yPosition,10).toString();
        const cleanedXPosition = parseInt(xPosition,10).toString();

        if(name === "UNUSED"){
            bayContent += `<div class="grid-item grid-unused" id="${name}"><div class="grid-item-content">${name[0]}</div></div>`;
        }else if(name === "NAN"){
            bayContent += `<div class="grid-item grid-nan" id="${name}"><div class="grid-item-content">${name[0]}</div></div>`;
        }else{
            bayContent += `<div class="grid-item grid-container" id="${cleanedYPosition},${cleanedXPosition}" onclick="tester((${cleanedYPosition}+','+ ${cleanedXPosition}))"><div class="grid-item-content">${name[0]}</div></div>`;
        }

       
      }
    }
    // console.log(content);
    bay.innerHTML = bayContent;
  }
  async function tester(){
    console.log("function invoked by id element: ");
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