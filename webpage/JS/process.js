

function processContent(content) {
    const lines = content.split('\n');

    //  Get the buffer item
    var bay = document.getElementById("bay_grid");
    var bayContent = "";
  
    for (const line of lines) {
      const match = line.match(/\[(\d+),(\d+)\], \{(\d+)\}, (\w+)/);
  
      if (match) {
        const [, yPosition, xPosition, mass, name] = match;

        if(name === "UNUSED"){
            bayContent += `<div class="grid-item grid-unused" id="${name}"><div class="grid-item-content">${name[0]}</div></div>`;
        }else if(name === "NAN"){
            bayContent += `<div class="grid-item grid-nan" id="${name}"><div class="grid-item-content">${name[0]}</div></div>`;
        }else{
            bayContent += `<div class="grid-item grid-container" id="${name}"><div class="grid-item-content">${name[0]}</div></div>`;
        }

       
      }
    }
    // console.log(content);
    bay.innerHTML = bayContent;
  }
  