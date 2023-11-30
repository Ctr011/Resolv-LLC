// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', () => {
    const form = document.querySelector('#uploadForm');
    form.addEventListener('submit', uploadFile);
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
    const fileInput = document.getElementById("file")
    const file = fileInput.files[0];    //  Get teh file

    const formData = new FormData();
    formData.append('file', file);

    try {
        const response = await fetch('/upload', {
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