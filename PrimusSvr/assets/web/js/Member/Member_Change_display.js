
/*
    Per Id des Members und einer GET function.
    Sollen alle Attribute wie z.B. Vorname,alter, Telefon, Poz, .... auf der Webseite angezeigt werden.
*/

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

/**/
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
    let CurrentUserDepartment   = DepartmentData.items[0];  //

    /* 
        currentUserMember
    */
    var inputElement_FirstName = document.getElementById('FirstName');    
    inputElement_FirstName.value = currentUserMember.firstName;           // 
    
    var inputElement_LastName = document.getElementById('LastName');    
    inputElement_LastName.value = currentUserMember.lastName;    

    var inputElement_birth_date = document.getElementById('birth_date');    
    inputElement_birth_date.value = currentUserMember.birthDate;  

    /*
        currentUserAdresse
    */
    var inputElement_Poz = document.getElementById('Poz');    
    inputElement_Poz.value = currentUserAdresse.postalCode;           //     

    var inputElement_residence = document.getElementById('residence');    
    inputElement_residence.value = currentUserAdresse.city;           // 

    var inputElement_street = document.getElementById('street');    
    inputElement_street.value = currentUserAdresse.street;           // 

    var inputElement_H_Number = document.getElementById('H_Number');    
    inputElement_H_Number.value = currentUserAdresse.houseNumber;           // 



    // ('Member_email').textContent = ${currentUserMember.email}
    // ('phoneNumber').textContent =  ${currentUserMember.phoneNumber}





    /*
        CurrentUserDepartment
    */
    var inputDepartment = document.getElementById('Department');

    

    



    //document.getElementById('FirstName').textContent = `Vorname: ${currentUserMember.firstName}`;
    
    //currentUserAdresse
    //document.getElementById('Poz').textContent = `Postleitzahl: ${currentUserAdresse.phoneNumber}`;
}
    
// check for single User.
function error_DB_Anomalie(memberData, adresseData)
{
    if(memberData[1] !== undefined)
    {
        alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    }

    // if(adresseData[1] !== undefined)
    // {
    //     alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    // }
}



