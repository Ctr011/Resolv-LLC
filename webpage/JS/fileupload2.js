// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#uploadForm');
    if(form){
    form.addEventListener('submit', uploadFile2, true);}
});


/**
 * @function uploadFile2
 * This function handles a file submission from a webpage with a form
 * It looks for a form element in the document, and processes the file info
 * @param {Event} event handles
 * @returns {Promise<void>}
 */
async function uploadFile2(event) {
    const form = event.currentTarget;
    const fileInput = document.getElementById("offload");
    const ids = document.createElement('id');
    const file = fileInput.files[0];    //  Get teh file
    const id = fileInput.form.id;

    const formData = new FormData();
    formData.append('offload', file);
    formData.append('id', id)

    try {
        const response = await fetch('/load', {
            method: 'POST',
            body: formData
        });

        const data = await response;
        console.log('Success:', data);
        console.log('ID Upload: ', id);
    } catch (error) {
        console.error('Error:', error);
    }

    // Stops page from reloading to submit the form
    event.preventDefault();
}
