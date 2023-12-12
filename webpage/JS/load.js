// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#userNotes');
    if(form){
    form.addEventListener('submit', loadcheck, true);}
});


/**
 * @function loadcheck
 * This file will handle the user login inputs from all employees
 * 
 * @param {Event} event handles the event settings
 * @returns {Promise<void>}
 */

async function loadcheck(event) {
    const form = event.currentTarget;
    const contn = document.getElementById("contn").value;
    const contw = document.getElementById('contw').value;
    document.getElementById("contn").value = '';
    document.getElementById("contw").value = '';
    // const ids = document.createElement('id');
    // const logins = login.value;    //  Get teh file
    // const id = login.form.id;

    const formData = new FormData();
    formData.append('contn', contn);
    formData.append('contw', contw);
    // formData.append('id', id);

    try {
        const response = await fetch('/contname', {
            method: 'POST',
            body: formData
        });

        const data = await response;
        console.log('Success:', data);
        console.log('Container Name: ', contn);
        console.log('Container Weight: ', contw);
    } catch (error) {
        console.error('Error:', error);
    }

    // Stops page from reloading to submit the form
    event.preventDefault();
}
