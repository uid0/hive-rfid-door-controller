use utf8;
package Access::Schema::Result::Mgroup;

# Created by DBIx::Class::Schema::Loader
# DO NOT MODIFY THE FIRST PART OF THIS FILE

=head1 NAME

Access::Schema::Result::Mgroup

=cut

use strict;
use warnings;

use base 'DBIx::Class::Core';

=head1 COMPONENTS LOADED

=over 4

=item * L<DBIx::Class::InflateColumn::DateTime>

=back

=cut

__PACKAGE__->load_components("InflateColumn::DateTime");

=head1 TABLE: C<mgroup>

=cut

__PACKAGE__->table("mgroup");

=head1 ACCESSORS

=head2 mgroup_id

  data_type: 'uuid'
  is_nullable: 0
  size: 16

=head2 name

  data_type: 'char'
  is_nullable: 1
  size: 32

=cut

__PACKAGE__->add_columns(
  "mgroup_id",
  { data_type => "uuid", is_nullable => 0, size => 16 },
  "name",
  { data_type => "char", is_nullable => 1, size => 32 },
);

=head1 PRIMARY KEY

=over 4

=item * L</mgroup_id>

=back

=cut

__PACKAGE__->set_primary_key("mgroup_id");

=head1 RELATIONS

=head2 item_mgroups

Type: has_many

Related object: L<Access::Schema::Result::ItemMgroup>

=cut

__PACKAGE__->has_many(
  "item_mgroups",
  "Access::Schema::Result::ItemMgroup",
  { "foreign.mgroup_id" => "self.mgroup_id" },
  { cascade_copy => 0, cascade_delete => 0 },
);

=head2 member_mgroups

Type: has_many

Related object: L<Access::Schema::Result::MemberMgroup>

=cut

__PACKAGE__->has_many(
  "member_mgroups",
  "Access::Schema::Result::MemberMgroup",
  { "foreign.mgroup_id" => "self.mgroup_id" },
  { cascade_copy => 0, cascade_delete => 0 },
);

=head2 items

Type: many_to_many

Composing rels: L</item_mgroups> -> item

=cut

__PACKAGE__->many_to_many("items", "item_mgroups", "item");

=head2 members

Type: many_to_many

Composing rels: L</member_mgroups> -> member

=cut

__PACKAGE__->many_to_many("members", "member_mgroups", "member");


# Created by DBIx::Class::Schema::Loader v0.07042 @ 2017-02-10 20:44:52
# DO NOT MODIFY THIS OR ANYTHING ABOVE! md5sum:9L72UzlCSxy94IY71RcU0w


# You can replace this text with custom code or comments, and it will be preserved on regeneration
1;
