// Set up the event listener for the form submission
document.addEventListener('DOMContentLoaded', (event) => {
    const form = document.querySelector('#userLogin');
    if(form){
        form.addEventListener('submit', userLogin, true);}
});


/**
 * @function userLogin
 * This file will handle the user login inputs from all employees
 * 
 * @param {Event} event handles the event settings
 * @returns {Promise<void>}
 */
async function userLogin(event) {
    const form = event.currentTarget;
    const login = document.getElementById("name").value;
    document.getElementById("name").value = '';
    // const ids = document.createElement('id');
    // const logins = login.value;    //  Get teh file
    // const id = login.form.id;

    const formData = new FormData();
    formData.append('name', login);
    // formData.append('id', id);

    try {
        const response = await fetch('/id', {
            method: 'POST',
            body: formData
        });

        const data = await response;
        console.log('Success:', data);
        console.log('User: ', login);
    } catch (error) {
        console.error('Error:', error);
    }

    // Stops page from reloading to submit the form
    event.preventDefault();
}
