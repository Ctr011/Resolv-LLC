// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#userNotes');
    if(form){
    form.addEventListener('submit', userNotes, true);}
});


/**
 * @function userNotes
 * This file will handle the user login inputs from all employees
 * 
 * @param {Event} event handles the event settings
 * @returns {Promise<void>}
 */

async function userNotes(event) {
    const form = event.currentTarget;
    const note = document.getElementById("nnote").value;
    document.getElementById("nnote").value = '';
    // const ids = document.createElement('id');
    // const logins = login.value;    //  Get teh file
    // const id = login.form.id;

    const formData = new FormData();
    formData.append('nnote', note);
    // formData.append('id', id);

    try {
        const response = await fetch('/notes', {
            method: 'POST',
            body: formData
        });

        const data = await response;
        console.log('Success:', data);
        console.log('Custom Notes: ', note);
    } catch (error) {
        console.error('Error:', error);
    }

    // Stops page from reloading to submit the form
    event.preventDefault();
}
