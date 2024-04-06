class PrimusApiClient {
    constructor(baseURL) {
        this.baseURL = baseURL;
    }

    async fetchData(url, method = 'GET', bodyData = null) {
        const options = {
            method: method,
            headers: {
                'Content-Type': 'application/json'
            }
        };

        if (bodyData) {
            options.body = JSON.stringify(bodyData);
        }

        const response = await fetch(url, options);

        if (!response.ok) {
            throw new Error(`HTTP error! Status: ${response.status}`);
        }

        return await response.json();
    }

    async getFiles() {
        const url = `${this.baseURL}/web/*`;
        return await this.fetchData(url);
    }

    async getRoot() {
        const url = `${this.baseURL}/`;
        return await this.fetchData(url);
    }

    async getMemberById(memberId) {
        const url = `${this.baseURL}/api/member/${memberId}`;
        return await this.fetchData(url);
    }

    async updateMember(memberId, memberData) {
        const url = `${this.baseURL}/api/member/${memberId}`;
        return await this.fetchData(url, 'PUT', memberData);
    }

    async createMember(memberData) {
        const url = `${this.baseURL}/api/member`;
        return await this.fetchData(url, 'POST', memberData);
    }

    async getMemberList(memberId, attribute, offset, limit) {
        const url = `${this.baseURL}/api/member/${memberId}/list/${attribute}?offset=${offset}&limit=${limit}`;
        return await this.fetchData(url);
    }

    async getMembersList(attribute, limit, offset) {
        const url = `${this.baseURL}/api/members/list/${attribute}?limit=${limit}&offset=${offset}`;
        return await this.fetchData(url);
    }

    async getMemberCount(attribute) {
        const url = `${this.baseURL}/api/members/count/${attribute}`;
        return await this.fetchData(url);
    }

    async createMemberDepartmentAssociation(memberId, departmentId) {
        const url = `${this.baseURL}/api/member/${memberId}/department/add/${departmentId}`;
        return await this.fetchData(url, 'POST');
    }

    async deleteMemberDepartmentDisassociation(memberId, departmentId) {
        const url = `${this.baseURL}/api/member/${memberId}/department/remove/${departmentId}`;
        return await this.fetchData(url, 'DELETE');
    }

    async createMemberAddressAssociation(memberId, addressData) {
        const url = `${this.baseURL}/api/member/${memberId}/address/add`;
        return await this.fetchData(url, 'POST', addressData);
    }

    async deleteMemberAddressDisassociation(memberId, addressId) {
        const url = `${this.baseURL}/api/member/${memberId}/address/remove/${addressId}`;
        return await this.fetchData(url, 'DELETE');
    }

    async addMemberAttendance(memberId, dateOfAttendance) {
        const url = `${this.baseURL}/api/member/${memberId}/attendance/${dateOfAttendance}`;
        return await this.fetchData(url, 'POST');
    }

    async deleteMemberAttendance(memberId, dateOfAttendance) {
        const url = `${this.baseURL}/api/member/${memberId}/attendance/${dateOfAttendance}`;
        return await this.fetchData(url, 'DELETE');
    }
}
