const int N = 200024;
int arr[N];
struct segtree {
	struct node {
		int val=0, tag=0, sz;
		int rv() { return val + tag * sz; }
	}seg[N<<2];
	void build(int l, int r, int id) {
		seg[id].sz = r - l + 1;
		if (l == r) {
			seg[id].val= arr[l];
			return;
		}
		int m = l + r>>1;
		build(l, m, id << 1);
		build(m + 1, r, id << 1 | 1);
		seg[id].val = seg[id << 1].val + seg[id << 1 | 1].val;
	}
	void push(int id) {
		seg[id << 1].tag += seg[id].tag;
		seg[id << 1 | 1].tag += seg[id].tag;
		seg[id].val = seg[id].rv();
		seg[id].tag = 0;
	}
	void modify(int ql, int qr, int id, int L, int R, int v) {
		if (ql >R || qr <L) return;
		if (ql <= L && qr >= R) {
			seg[id].tag += v;
			return;
		}
		int m = L + R>>1;
		modify(ql, qr, id << 1, L, m, v);
		modify(ql, qr, id << 1 | 1, m + 1, R, v);
		seg[id].val = seg[id << 1].rv() + seg[id << 1 | 1].rv();
	}
	int query(int ql, int qr, int id, int L, int R) {
		if (ql >=R || qr <=L) return 0;
		if (ql <= L && qr >= R) {
			return seg[id].rv();
		}
		push(id);
		int m = L + R >>1;
		return query(ql, qr, id << 1, L, m) + query(ql, qr, id << 1 | 1, m + 1, R);
	}
}sgt;
