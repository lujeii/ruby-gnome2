/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2011  Ruby-GNOME2 Project Team
 *  Copyright (C) 2002-2005 Ruby-GNOME2 Project Team
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

#define RG_TARGET_NAMESPACE cLabel
#define _SELF(s) (GTK_LABEL(RVAL2GOBJ(s)))

static VALUE
label_initialize(int argc, VALUE *argv, VALUE self)
{
    VALUE label, with_mnemonic;
    GtkWidget* widget = NULL;

    rb_scan_args(argc, argv, "02", &label, &with_mnemonic);
    if (NIL_P(with_mnemonic) || ! RVAL2CBOOL(with_mnemonic)){
        widget = gtk_label_new(NIL_P(label)?NULL:RVAL2CSTR(label));
    } else {
        widget = gtk_label_new_with_mnemonic(NIL_P(label)?NULL:RVAL2CSTR(label));
    }

    RBGTK_INITIALIZE(self, widget);
    return Qnil;
}

static VALUE
label_set_text_only(VALUE self, VALUE text)
{
    gtk_label_set_text(_SELF(self), RVAL2CSTR(text));
    return text;
}

static VALUE
label_set_text(int argc, VALUE *argv, VALUE self)
{
    VALUE label, with_mnemonic;

    rb_scan_args(argc, argv, "02", &label, &with_mnemonic);
    if (NIL_P(with_mnemonic) || ! RVAL2CBOOL(with_mnemonic)){
        gtk_label_set_text(_SELF(self), RVAL2CSTR(label));
    } else {
        gtk_label_set_text_with_mnemonic(_SELF(self), RVAL2CSTR(label));
    }
    return self;
}

static VALUE
label_set_markup_only(VALUE self, VALUE text)
{
    gtk_label_set_markup(_SELF(self), RVAL2CSTR(text));
    return text;
}

static VALUE
label_set_markup(int argc, VALUE *argv, VALUE self)
{
    VALUE str, with_mnemonic;
    rb_scan_args(argc, argv, "02", &str, &with_mnemonic);

    if (NIL_P(with_mnemonic) || ! RVAL2CBOOL(with_mnemonic)){
        gtk_label_set_markup(_SELF(self), RVAL2CSTR(str));
    } else {
        gtk_label_set_markup_with_mnemonic(_SELF(self), RVAL2CSTR(str));
    }        
    return self;
}

static VALUE
label_get_layout_offsets(VALUE self)
{ 
    gint x, y;
    gtk_label_get_layout_offsets(_SELF(self), &x, &y);
    return rb_ary_new3(2, INT2NUM(x), INT2NUM(y));
}

static VALUE
label_get_text(VALUE self)
{
    return CSTR2RVAL(gtk_label_get_text(_SELF(self)));
}

static VALUE
label_select_region(VALUE self, VALUE start_offset, VALUE end_offset)
{
    gtk_label_select_region(_SELF(self), NUM2INT(start_offset), NUM2INT(end_offset));
    return self;
}

static VALUE
label_get_layout(VALUE self)
{
    return GOBJ2RVAL(gtk_label_get_layout(_SELF(self)));
}

static VALUE
label_get_selection_bounds(VALUE self)
{
    gint start, end;
    gboolean ret = gtk_label_get_selection_bounds(_SELF(self), &start, &end);
    return ret ? rb_ary_new3(2, INT2NUM(start), INT2NUM(end)) : Qnil;
}

void 
Init_gtk_label(void)
{
    VALUE RG_TARGET_NAMESPACE = G_DEF_CLASS(GTK_TYPE_LABEL, "Label", mGtk);

    rb_define_method(RG_TARGET_NAMESPACE, "initialize", label_initialize, -1);
    rb_define_method(RG_TARGET_NAMESPACE, "text", label_get_text, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_text", label_set_text, -1);
    rb_define_method(RG_TARGET_NAMESPACE, "text=", label_set_text_only, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "set_markup", label_set_markup, -1);
    rb_define_method(RG_TARGET_NAMESPACE, "markup=", label_set_markup_only, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "layout_offsets", label_get_layout_offsets, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "select_region", label_select_region, 2);
    rb_define_method(RG_TARGET_NAMESPACE, "layout", label_get_layout, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "selection_bounds", label_get_selection_bounds, 0);
}
