//  Godfrey (12/13): This file will be used to process the ocntent of the 
//  bay, as well as 

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
  