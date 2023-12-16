// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#startProgram');
    if(form){
    form.addEventListener('submit', startProgram, true);}
});


/**
 * @function startProgram
 * This function handles a file submission from a webpage with a form
 * It looks for a form element in the document, and processes the file info
 * @param {Event} event handles
 * @returns {Promise<void>}
 */
async function startProgram(event) {
    const form = event.currentTarget;
    const fileInput = document.getElementById("bth");

    const formData = new FormData();
    formData.append('bth', fileInput);


    try {
        const response = await fetch('/start', {
            method: 'POST',
            body: formData
        });

        const data = await response;
        console.log('Success:', data);
    } catch (error) {
        console.error('Error:', error);
    }

    // Stops page from reloading to submit the form
    event.preventDefault();
}
