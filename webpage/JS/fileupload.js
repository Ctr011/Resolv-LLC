// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#uploadForm');
    if(form){
    form.addEventListener('submit', uploadFile, true);}
});


/**
 * @function uploadFile
 * This function handles a file submission from a webpage with a form
 * It looks for a form element in the document, and processes the file info
 * @param {Event} event handles
 * @returns {Promise<void>}
 */
async function uploadFile(event) {
    const form = event.currentTarget;
    const fileInput = document.getElementById("bala");
    const ids = document.createElement('id');
    const file = fileInput.files[0];    //  Get teh file
    const id = fileInput.form.id;

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
        const response = await fetch('/balanced', {
            method: 'POST',
            body: formData
        });

        const data = await response.json();
        console.log('Success:', data);
        console.log('ID Upload: ', id);
    } catch (error) {
        console.error('Error:', error);
    }
    // window.location.href ="http://localhost:8080/fileupload.html";
    window.location.replace("http://localhost:8080/balance.html");
    // Stops page from reloading to submit the form
    event.preventDefault();
}

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

    bay.innerHTML = bayContent;
  }
  