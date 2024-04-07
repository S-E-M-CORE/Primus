
displayController();

async function displayController()
{
    let memberData      = await getMemberData();       // gibt uns das Adresse Jason Objekt.
    let adresseData     = await getAdresseData();     // gibt uns das Adresse Jason Objekt.
    let DepartmentData  = await getDepartment();

    
    updateHTML(memberData, adresseData, DepartmentData);        // ändert den angezeigten Text.
}

async function getMemberData() 
{
    try 
    {
        const memberId = 2; // Beispielhaft festgelegte Mitglieds-ID
        const apiClient = new PrimusApiClient(`http://localhost:8000`);

        const memberData = await apiClient.getMemberById(memberId);
        JSON.stringify(memberData);
        return memberData;
    } 
    catch (error) 
    {
        console.error('Fehler beim Abrufen der Mitgliedsdaten:', error);
        // Hier kannst du die Fehlerbehandlung ergänzen, z.B. eine Fehlermeldung auf der Seite anzeigen
    }
}

/*
*/ 
async function getAdresseData()
{
    try 
    {
        const memberId = 2; // Beispielhaft festgelegte Mitglieds-ID
        const attributes = 'addresses';
        const limit = 2;
        const apiClient = new PrimusApiClient(`http://localhost:8000`);

        const addresseData = await apiClient.getMemberList(memberId, attributes, 0, limit);
        JSON.stringify(addresseData);
        return addresseData;

    } 
    catch (error) 
    {
        console.error('Fehler beim Abrufen der Adressedaten:', error);
        // Hier kannst du die Fehlerbehandlung ergänzen, z.B. eine Fehlermeldung auf der Seite anzeigen
    }
}

/*
*/
async function getDepartment()
{
    try 
    {
        const memberId = 2; // Beispielhaft festgelegte Mitglieds-ID
        const attributes = 'departments';
        const limit = 2;
        const apiClient = new PrimusApiClient(`http://localhost:8000`);

        const DepartmentData = await apiClient.getMemberList(memberId, attributes, 0, limit);
        JSON.stringify(DepartmentData);
        return DepartmentData;
    } 
    catch (error) 
    {
        console.error('Fehler beim Abrufen der Mitgliedsdaten:', error);
        // Hier kannst du die Fehlerbehandlung ergänzen, z.B. eine Fehlermeldung auf der Seite anzeigen
    } 
}

/*
Die Funktion ist dazu alle infomationen die von allen benötigten Jason Objekten kommen  

Parameters:
    memberData - zeigen Vorname
    adresseData - zeigen Postleitzahl, Wohnort, Straßename, Hausnummer
*/
function updateHTML(memberData , adresseData, DepartmentData) 
{
    error_DB_Anomalie(memberData, adresseData);     // wir überprüfen die Ressource die wir bekommen haben.

    let currentUserMember       = memberData[0];            // 0 weil wir nur nach einem User Fragen wollen.
    let currentUserAdresse      = adresseData.items[0];     //

    /* 
        currentUserMember
    */
    var inputElement_FirstName = document.getElementById('FirstName');    
    inputElement_FirstName.value = currentUserMember.firstName;           // 
    
    var inputElement_LastName = document.getElementById('LastName');    
    inputElement_LastName.value = currentUserMember.lastName;    

    var inputElement_birth_date = document.getElementById('birth_date');    
    inputElement_birth_date.value = currentUserMember.birthDate;  

    var inputElement_email = document.getElementById('Member_email');    
    inputElement_email.value = currentUserMember.email;  

    var inputElement_phoneNumber = document.getElementById('phoneNumber');    
    inputElement_phoneNumber.value = currentUserMember.phoneNumber;  

    var inputElement_joindate = document.getElementById('joindate');    
    inputElement_joindate.value = currentUserMember.createDate;  

    var inputElement_notes = document.getElementById('notes');    
    inputElement_notes.value = currentUserMember.notes; 

    /*
        currentUserAdresse
    */
    var inputElement_Poz = document.getElementById('Poz');    
    inputElement_Poz.value = currentUserAdresse.postalCode;             //     

    var inputElement_residence = document.getElementById('residence');    
    inputElement_residence.value = currentUserAdresse.city;             // 

    var inputElement_street = document.getElementById('street');    
    inputElement_street.value = currentUserAdresse.street;              // 

    var inputElement_H_Number = document.getElementById('H_Number');    
    inputElement_H_Number.value = currentUserAdresse.houseNumber;       // 

    /*
        CurrentUserDepartment
    */
    var inputDepartment = document.getElementById('Department_dropdown');
    checkDepartment(DepartmentData, inputDepartment);

}

function checkDepartment(DepartmentData, inputDepartment)
{
    if (DepartmentData.count <= 0) 
    {
        if (DepartmentData.items[0] && DepartmentData.items[1] && DepartmentData.items[2]) 
        {
            inputDepartment.value = inputDepartment.items[0].value;
        }
        // Bogen und Luftgewehre
        if (DepartmentData.items[0] && DepartmentData.items[1]) 
        {
            inputDepartment.value = "VIP-Paket Bogen und Luft Abteilungen";
        } 
        else if (DepartmentData.items[0] && DepartmentData.items[2]) 
        {
            inputDepartment.value = "VIP-Paket Bogen und Feuerwaffen Abteilungen";
        } 
        else if (DepartmentData.items[1] && DepartmentData.items[2]) 
        {
            inputDepartment.value = "VIP-Paket Luft und Feuerwaffen Abteilungen";
        }
    } 
    else if (DepartmentData.count <= 0) 
    {
        if (DepartmentData.items[0]) 
        {
            inputDepartment.value = "nur Bogenschießen";
        } 
        else if (DepartmentData.items[1]) 
        {
            inputDepartment.value = "Nur Luftdruckwaffen";
        } 
        else if (DepartmentData.items[2]) 
        {
            inputDepartment.value = "Nur Feuerwaffen";
        }
    } 
    else 
    {
        // Default-Wert setzen, wenn keine Bedingung zutrifft
        inputDepartment.value = "none";
    }
}

// check for single User.
function error_DB_Anomalie(memberData, adresseData)
{
    if(memberData[1] !== undefined)
    {
        alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    }
}



