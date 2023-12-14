/**
 * @function checkLoggedIn
 * 
 * @param NONE
 * @return bool: Based on if the use is logged in or not
 */
async function logIn(){
    const response = await fetch('/upload', {
        method: 'GET'
    });

    var status = await response.status;

    if(status === 200){
        window.location = "/upload"
    }
}