void
horizgrid(Monitor *m) {
	Client *c;
	unsigned int n, i;
	int w = 0;
	int ntop, nbottom = 0;

	/* Count windows */
    for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
    if(n == 0) {
        return;
    } else if(n == 1) { /* Just fill the whole screen */
        c = nexttiled(m->clients);
        resize(c, m->wx + gappx, m->wy + gappx, m->ww - 2*c->bw - 2*gappx, m->wh - 2*c->bw - 2*gappx, False);
    } else if(n == 2) { /* Split vertically */
        w = m->ww / 2;
        c = nexttiled(m->clients);
        resize(c, m->wx + gappx, m->wy + gappx, w - 2*c->bw - 2*gappx, m->wh - 2*c->bw - 2*gappx, False);
        c = nexttiled(c->next);
        resize(c, m->wx + w + gappx, m->wy + gappx, w - 2*c->bw - 2*gappx, m->wh - 2*c->bw - 2*gappx, False);
    } else {
		ntop = n / 2;
		nbottom = n - ntop;
		for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
			if(i < ntop)
		        resize(c, m->wx + i * m->ww / ntop + gappx, m->wy + gappx, m->ww / ntop - (2*c->bw) - 2 * gappx, m->wh / 2 - (2*c->bw) - 2 * gappx, False);	
			else
                resize(c, m->wx + (i - ntop) * m->ww / nbottom + gappx, m->wy + m->wh / 2 + gappx, m->ww / nbottom - (2*c->bw) - 2 * gappx, m->wh / 2 - (2*c->bw) - 2 * gappx, False);		
        }
	}
}
