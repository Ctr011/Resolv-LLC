document.addEventListener("DOMContentLoaded", (event){
    const form = document.querySelector("#load");
})

async function completeSystem(event){
    const form = event.currentTarget;
    const final = document.getElementById('final');
    const formData = new FormData();

    formData.append("finished", "yes");
    try {
    const response = await fetch('/done', {
        method: 'POST',
        body: formData
    });

    const data = await response;
    console.log('Success:', data);
} catch (error) {
    console.error('Error:', error);
}
    event.preventDefault();
}