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

    async getMemberById(memberId) {
        const url = `${this.baseURL}/api/member/${memberId}`;
        const response = await fetch(url);
        return await response.json();
    }

    async getTotalMemberCount() {
        const url = `${this.baseURL}/api/members/total/count`;
        const response = await fetch(url);
        return await response.text();
    }

    async getMemberCountActive() {
        const url = `${this.baseURL}/api/members/active/count`;
        const response = await fetch(url);
        return await response.json();
    }

    async getMemberCountInactive() {
        const url = `${this.baseURL}/api/members/inactive/count`;
        const response = await fetch(url);
        return await response.json();
    }

    async getAllMembers(offset, limit) {
        const url = `${this.baseURL}/api/members/total/all?offset=${offset}&limit=${limit}`;
        const response = await fetch(url);
        return await response.json();
    }

    async deactivateMemberById(memberId) {
        const url = `${this.baseURL}/api/members/${memberId}/deactivate`;
        const response = await fetch(url, { method: 'PUT' });
        return await response.json();
    }

    async activateMemberById(memberId) {
        const url = `${this.baseURL}/api/members/${memberId}/activate`;
        const response = await fetch(url, { method: 'PUT' });
        return await response.json();
    }
}