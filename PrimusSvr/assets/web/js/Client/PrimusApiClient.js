class PrimusApiClient {
    constructor(baseURL) {
        this.baseURL = baseURL;
    }

    async getFiles() {
        const url = `${this.baseURL}/web/*`;
        const response = await fetch(url);
        return await response.json();
    }

    async getRoot() {
        const url = `${this.baseURL}/`;
        const response = await fetch(url);
        return await response.json();
    }

    async getMemberById(memberId) {
        const url = `${this.baseURL}/api/member/${memberId}`;
        const response = await fetch(url);
        return await response.json();
    }

    async updateMember(memberId, memberData) {
        const url = `${this.baseURL}/api/member/${memberId}`;
        const response = await fetch(url, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(memberData)
        });
        return await response.json();
    }

    async createMember(memberData) {
        const url = `${this.baseURL}/api/member`;
        const response = await fetch(url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(memberData)
        });
        return await response.json();
    }

    async getMemberList(memberId, attribute, offset, limit) {
        const url = `${this.baseURL}/api/member/${memberId}/list/${attribute}?offset=${offset}&limit=${limit}`;
        const response = await fetch(url);
        return await response.json();
    }

    async getMembersList(attribute, limit, offset) {
        const url = `${this.baseURL}/api/members/list/${attribute}?limit=${limit}&offset=${offset}`;
        const response = await fetch(url);
        return await response.json();
    }

    async getMemberCount(attribute) {
        const url = `${this.baseURL}/api/member/count/${attribute}`;
        const response = await fetch(url);
        return await response.json();
    }

    async createMemberDepartmentAssociation(memberId, departmentId) {
        const url = `${this.baseURL}/api/member/${memberId}/department/add/${departmentId}`;
        const response = await fetch(url, { method: 'POST' });
        return await response.json();
    }

    async deleteMemberDepartmentDisassociation(memberId, departmentId) {
        const url = `${this.baseURL}/api/member/${memberId}/department/remove/${departmentId}`;
        const response = await fetch(url, { method: 'DELETE' });
        return await response.json();
    }

    async createMemberAddressAssociation(memberId, addressData) {
        const url = `${this.baseURL}/api/member/${memberId}/address/add`;
        const response = await fetch(url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(addressData)
        });
        return await response.json();
    }

    async deleteMemberAddressDisassociation(memberId, addressId) {
        const url = `${this.baseURL}/api/member/${memberId}/address/remove/${addressId}`;
        const response = await fetch(url, { method: 'DELETE' });
        return await response.json();
    }

    async addMemberAttendance(memberId, dateOfAttendance) {
        const url = `${this.baseURL}/api/member/${memberId}/attendance/${dateOfAttendance}`;
        const response = await fetch(url, { method: 'POST' });
        return await response.json();
    }

    async deleteMemberAttendance(memberId, dateOfAttendance) {
        const url = `${this.baseURL}/api/member/${memberId}/attendance/${dateOfAttendance}`;
        const response = await fetch(url, { method: 'DELETE' });
        return await response.json();
    }
}
