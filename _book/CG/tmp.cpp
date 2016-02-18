bool PtOnSegment(Pt s, Pt t, Pt a) {
	return !det(a-s, a-t) && min(s.x, t.x) <= a.x && a.x <= max(s.x, t.x) &&
		min(s.y, t.y) <= a.y && a.y <= max(s.y, t.y);
}
