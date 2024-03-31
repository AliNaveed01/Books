document.addEventListener('DOMContentLoaded', function() {
    const form = document.getElementById('jobApplicationForm');
    const viewAsTableBtn = document.getElementById('viewAsTableBtn');
    const applicationTable = document.getElementById('applicationTable');
    let applications = [];

    form.addEventListener('submit', function(event) {
        event.preventDefault();

        if (validateForm()) {
            const formData = new FormData(form);
            const applicationData = Object.fromEntries(formData.entries());
            applications.push(applicationData);
            console.log(applicationData);
            form.reset();
        }
    });

    viewAsTableBtn.addEventListener('click', function() {
        displayApplicationsAsTable();
    });

    function validateForm() {
        const inputs = form.querySelectorAll('input, textarea, select');
        let isValid = true;

        inputs.forEach(input => {
            if (input.hasAttribute('required') && !input.value.trim()) {
                isValid = false;
                input.classList.add('error');
            } else {
                input.classList.remove('error');
            }
        });

        return isValid;
    }

    function displayApplicationsAsTable() {
        let tableHTML = '<table border="1">';
        tableHTML += '<thead><tr><th>Name</th><th>Email</th><th>Phone Number</th><th>Resume</th><th>Cover Letter</th></tr></thead>';
        tableHTML += '<tbody>';

        applications.forEach(function(application) {
            tableHTML += `<tr><td>${application.firstName} ${application.lastName}</td><td>${application.email}</td><td>${application.phoneNumber}</td><td>${application.resume}</td><td>${application.coverLetter}</td></tr>`;
        });

        tableHTML += '</tbody></table>';

        applicationTable.innerHTML = tableHTML;
    }
});
