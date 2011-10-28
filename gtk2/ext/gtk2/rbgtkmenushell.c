/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2011  Ruby-GNOME2 Project Team
 *  Copyright (C) 2002-2004 Ruby-GNOME2 Project Team
 *  Copyright (C) 1998-2000 Yukihiro Matsumoto,
 *                          Daisuke Kanda,
 *                          Hiroshi Igarashi
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include "global.h"

#define RG_TARGET_NAMESPACE cMenuShell
#define _SELF(self) (GTK_MENU_SHELL(RVAL2GOBJ(self)))
#define RVAL2WIDGET(w) (GTK_WIDGET(RVAL2GOBJ(w)))

static VALUE
mshell_append(VALUE self, VALUE child)
{
    gtk_menu_shell_append(_SELF(self),RVAL2WIDGET(child));
    G_CHILD_ADD(self, child);
    return self;
}

static VALUE
mshell_prepend(VALUE self, VALUE child)
{
    gtk_menu_shell_prepend(_SELF(self), RVAL2WIDGET(child));
    G_CHILD_ADD(self, child);
    return self;
}

static VALUE
mshell_insert(VALUE self, VALUE child, VALUE pos)
{
    gtk_menu_shell_insert(_SELF(self), RVAL2WIDGET(child),
                          NUM2INT(pos));
    G_CHILD_ADD(self, child);
    return self;
}

static VALUE
mshell_deactivate(VALUE self)
{
    gtk_menu_shell_deactivate(_SELF(self));
    return self;
}

static VALUE
mshell_select_item(VALUE self, VALUE menu_item)
{
    gtk_menu_shell_select_item(_SELF(self), RVAL2WIDGET(menu_item));
    return self;
}

#if GTK_CHECK_VERSION(2,2,0)
static VALUE
mshell_select_first(VALUE self, VALUE search_sensitive)
{
    gtk_menu_shell_select_first(_SELF(self), RVAL2CBOOL(search_sensitive));
    return self;
}
#endif

static VALUE
mshell_deselect(VALUE self)
{
    gtk_menu_shell_deselect(_SELF(self));
    return self;
}

static VALUE
mshell_activate_item(VALUE self, VALUE menu_item, VALUE force_deactivate)
{
    gtk_menu_shell_activate_item(_SELF(self), RVAL2WIDGET(menu_item), 
                                 RVAL2CBOOL(force_deactivate));
    return self;
}

void 
Init_gtk_menu_shell(void)
{
    VALUE RG_TARGET_NAMESPACE = G_DEF_CLASS(GTK_TYPE_MENU_SHELL, "MenuShell", mGtk);

    rb_define_method(RG_TARGET_NAMESPACE, "append", mshell_append, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "prepend", mshell_prepend, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "insert", mshell_insert, 2);
    rb_define_method(RG_TARGET_NAMESPACE, "deactivate", mshell_deactivate, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "select_item", mshell_select_item, 1);
#if GTK_CHECK_VERSION(2,2,0)
    rb_define_method(RG_TARGET_NAMESPACE, "select_first", mshell_select_first, 1);
#endif
    rb_define_method(RG_TARGET_NAMESPACE, "deselect", mshell_deselect, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "activate_item", mshell_activate_item, 2);
    /* GtkMenuDirectionType */
    G_DEF_CLASS(GTK_TYPE_MENU_DIRECTION_TYPE, "DirectionType", RG_TARGET_NAMESPACE);
    G_DEF_CONSTANTS(RG_TARGET_NAMESPACE, GTK_TYPE_MENU_DIRECTION_TYPE, "GTK_MENU_");
}
