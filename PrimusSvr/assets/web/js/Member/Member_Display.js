
/*
    Per Id des Members und einer GET function.
    Sollen alle Attribute wie z.B. Vorname,alter, Telefon, Poz, .... auf der Webseite angezeigt werden.
*/

displayController();

async function displayController()
{
    let memberData      = await displayMemberData();    // gibt uns das Adresse Jason Objekt.
    let adresseData     = await displayAdresseData();   // gibt uns das Adresse Jason Objekt.
    let DepartmentData  = await getDepartment();

    updateHTML(memberData, adresseData, DepartmentData);        // ändert den angezeigten Text.
}

async function displayMemberData() 
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
async function displayAdresseData()
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
        const limit = 10;
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
    let currentUserAddresse     = adresseData.items[0];     //

    // currentUserMember
    document.getElementById('FirstName').textContent    = `Vorname: ${currentUserMember.firstName}`;
    document.getElementById('LastName').textContent     = `Nachname: ${currentUserMember.lastName}`;
    document.getElementById('date').textContent         = `Geburtstag: ${currentUserMember.birthDate}`;
    document.getElementById('Member_email').textContent = `Email address: ${currentUserMember.email}`;
    document.getElementById('phoneNumber').textContent  = `Telefonnummer: ${currentUserMember.phoneNumber}`;
    document.getElementById('joindate').textContent  = `Einstiegdatum: ${currentUserMember.createDate}`;
    document.getElementById('notes').textContent  = `Notizen oder Kommentare: ${currentUserMember.notes}`;
    

    //currentUserAdresse
    document.getElementById('Poz').textContent          = `Postleitzahl: ${currentUserAddresse.postalCode}`;
    document.getElementById('residence').textContent    = `Wohnort: ${currentUserAddresse.city}`;
    document.getElementById('street').textContent       = `Straßename: ${currentUserAddresse.street}`;
    document.getElementById('H_Number').textContent     = `Hausnummer: ${currentUserAddresse.houseNumber}`;

    let departmentsString = ""; 

    //CurrentUserDepartment
    for(var i = 0; i < DepartmentData.count; i++) // er kann mehren Departments angehören. 
    {
        if(i !== 0)
        {
            departmentsString =  departmentsString + "," + DepartmentData.items[i].name;
        }
        else 
        {
            departmentsString =  departmentsString + DepartmentData.items[i].name;
        }
    }

    document.getElementById('membership').textContent = `Mitgliedschaften: ${departmentsString}`;

    // Extra information
    //document.getElementById('membership').textContent    = Mitgliedschaften: ${.}`;
    //document.getElementById('joindate').textContent      = Einstiegdatum: ${.}`;
    //document.getElementById('notes').textContent         = Notizen und Kommentare: ${.}`;
}
    
// check for single User.
function error_DB_Anomalie(memberData, adresseData)
{
    if(memberData[1] !== undefined)
    {
        alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    }

    if(adresseData[1] !== undefined)
    {
        alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    }
}



